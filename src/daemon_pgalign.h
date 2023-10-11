#ifndef __UVMTD_DAEMON_PGALIGN_H__
#define __UVMTD_DAEMON_PGALIGN_H__

struct daemon_pgalign_conf {
	/*
	 * Delay between check clusters.
	 * If 0, there will be no delay 
	 */
	unsigned int sleept;

	/*
	 * Number of pages to allocate.
	 */
	unsigned int npages;
};

/*
 * Void * assumed to be type
 * erased daemon_pgalign_conf
 * struct.
 */
int daemon_pgalign(void *);

#endif /* __UVMTD_DAEMON_PGALIGN_H__ */
