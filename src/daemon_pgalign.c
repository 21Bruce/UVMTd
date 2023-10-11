/* Copyright (c) Bruce Jagid 2023 
 * **********************************************************************
 * daemon_pgalign is a simple configurable daemon for testing memory
 * integrity. It allocates a configurable amount of pages of memory,
 * checks if those pages are zero-aligned on a page boundary,
 * then sleeps for a configurable amount of time or no time at all.  
 * **********************************************************************
 */

#include "daemon_pgalign.h"
#include "elib.h"

#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>

typedef unsigned char byte;

/*
 * Daemon_pgalign function is used
 * as a daemon to check the integrity
 * of page allocations with respect
 * to alignment.
 */
int 
daemon_pgalign(void *config)
{
	/*
	 * Get system page size.
	 */
	unsigned long pgsize = sysconf(_SC_PAGESIZE);
	dlog("Detected system page size to be %d.", pgsize);

	/*
	 * Cast config to daemon specific
	 * config struct and check defaults.
	 */
	struct daemon_pgalign_conf *conf = (struct daemon_pgalign_conf *) config; 
	unsigned int sleept = conf->sleept;
	unsigned int npages = conf->npages > 0 ? conf->npages : 10;
	dlog("Config sleep time is %d and page number is %d.", sleept, npages);

	/*
	 * Allocate space for map ptrs.
	 */
	byte **maps = malloc(npages * sizeof(*maps));

	/*
	 * Main loop of daemon
	 */
	unsigned long i;
	unsigned long j;
	for (; ;) {
		/*
		 * Map in npages.
		 */
		for (i = 0; i < npages; i++) {
			maps[i] = mmap(NULL, pgsize, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
			/*
			 * If any map is NULL,
			 * fail.
			 */
			if (maps[i] == NULL) {
				for (j = 0; j < i; j++)
					munmap(maps[j], pgsize);
				free(maps);
				ddie(ERR_MEM_STAT, "Failed memory allocation.");
			}
			/*
			 * If any map is not aligned,
			 * fail. Should find better 
			 * method of doing this.
			 */
			if ((unsigned long)maps[i] % pgsize != 0) {
				for (j = 0; j <= i; j++)
					munmap(maps[j], pgsize);
				free(maps);
				ddie(ERR_INT_STAT, "Expected %p to be aligned on %l, but it is not.", maps[i], pgsize);
			}	
		}

		/*
		 * Free memory after checks.
		 */
		for (i = 0; i < npages; i++) {
			munmap(maps[i], pgsize);
		}

		/*
		 * If sleep is set, sleep.
		 */
		if (sleept)
			sleep(sleept);
	}		

	/*
	 * NOT REACHED.
	 */
	free(maps);
	return 0;

}


