#ifndef __UVMTD_DAEMONIZE_H__
#define __UVMTD_DAEMONIZE_H__

typedef int (daemonf)(void*);

void spawn(char *, daemonf *, void *);

#endif /* __UVMTD_DAEMONIZE_H__ */
