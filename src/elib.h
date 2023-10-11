#ifndef __UVMTD_ELIB_H__
#define __UVMTD_ELIB_H__

/*
 * Error functions for use in
 * main process.
 */
void die(const char* restrict, ...);

/*
 * Error functions for use in
 * daemon process.
 */
void derr(const char* restrict, ...);

#define ddie(stat, ...) 	\
do {				\
	derr(__VA_ARGS__); 	\
	return stat; 	 	\
} while(0)

/*
 * Error status codes used by daemons.
 */ 

/*
 * Error status when memory cannot
 * be allocated. 
 */ 
#define ERR_MEM_STAT 65

/*
 * Error status when memory integrity 
 * has been violated.
 */ 
#define ERR_INT_STAT 66

#endif /* __UVMTD_ELIB_H__ */
