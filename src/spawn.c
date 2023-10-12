/* Copyright (c) Bruce Jagid 2023 
 * **********************************************************************
 * Spawn takes a function and forks it into a daemon, changing the 
 * appropriate process specific metadata required to run the function
 * in the background of the system. This implementation is heavily
 * reliant on Chapter 13, Figure 13.1 of "Advanced Programming in The
 * Unix Environment" by W. Richard Stevens.
 * **********************************************************************
 */

#include "spawn.h"
#include "elib.h"

#include <syslog.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>

/* Spawns a properly daemonized function
 * whilst allowing parent process to 
 * resume operation. This allows
 * multiple daemons to spawn from the 
 * same main. Each daemon is permitted
 * a config struct.
 */
void 
spawn(char *dname, daemonf *df, void *config)
{
	int			i, fd0, fd1, fd2, dstat;
	pid_t			pid;
	struct rlimit 		rl;	
	struct sigaction 	sa;	

	/*
	 * Clear file creation mask.
	 */
	umask(0);

	/*
	 * Get maximum number of file descriptors.
	 */
	if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
		die("Attempted to spawn %s daemon, can't get file limit", dname);
	/*
	 * Become a session leader to lose controlling TTY.
	 */
	if ((pid = fork()) < 0)
		die("Attempted to spawn %s daemon, can't fork", dname);
	if (pid != 0) /* parent */
		return;
	setsid();

	/*
	 * Ensure future opens won't allocate controlling TTYs.
	 */
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		die("Attempted to spawn %s daemon, can't ignore SIGHUP", dname);
	if ((pid = fork()) < 0)
		die("Attempted to spawn %s daemon, can't fork", dname);
	if (pid != 0) /* parent */
		exit(0);

	/*
	 * Change the current working directory to root so
	 * we won't prevent file systems from being unmounted.
	 */
	if (chdir("/") < 0)
		die("Attempted to spawn %s daemon, can't change directory to /", dname);

	/*
	 * Close all file descriptors.
	 */
	if (rl.rlim_max == RLIM_INFINITY)
		rl.rlim_max = 1024;
	for (i = 0; i < rl.rlim_max; i++)
		close(i);

	/*
	 * Attach file descriptors 0, 1, and 2 to /dev/null. 
	 */
	fd0 = open("/dev/null", O_RDWR);
	fd1 = dup(0); 
	fd2 = dup(0); 

	/*
	 * Append a 'd' to dname
	 */
	int nlen = strlen(dname);
	char *name = malloc((nlen + 2) * sizeof *name);
	strlcpy(name, dname, nlen + 2);
	name[nlen] = 'd';
	name[nlen+1] = '\0';

	/*
	 * Initialize the log file.
	 */ 	
	openlog(name, LOG_CONS, LOG_DAEMON);
	if (fd0 != 0 || fd1 != 1 || fd2 != 2) {  
		syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
		closelog();
		free(name);
		exit(1);
	}

	/*
	 * Set process title.
	 */
	setproctitle("%s", name);

	/*
	 * Pass control to daemon. Save
	 * resulting status.
	 */
	dstat = (*df)(config);

	/*
	 * Close syslog.
	 */
	closelog();

	/*
	 * Release Resources.
	 */
	free(name);
	
	/*
	 * Exit with saved status.
	 */
	exit(dstat);

	/*
	 * NOT REACHED
	 */
}
