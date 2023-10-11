#ifndef __UVMTD_ELIB_H__
#define __UVMTD_ELIB_H__

void die(const char* restrict, ...);

void derr(const char* restrict, ...);

#define ddie(stat, ...) 	\
do {				\
	derr(__VA_ARGS__); 	\
	return stat; 	 	\	
} while(0)

#endif /* __UVMTD_ELIB_H__ */
