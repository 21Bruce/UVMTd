#ifndef __UVMTD_DAEMON_LINMAP_H__
#define __UVMTD_DAEMON_LINMAP_H__

/*
 * Linear Map Daemon Config 
 */
struct daemon_linmap_conf {
	/*
	 * Time to sleep between allocations.
	 */
	unsigned int 	sleept;
	/*
	 * Number of pages to allocate every cycle 
	 */
	unsigned int 	npages;
};

/*
 * Void * assumed to be a type erased
 * daemon_linmap_conf struct
 */ 
int daemon_linmap(void *);

#endif /* __UVMTD_DAEMON_LINMAP_H__ */
