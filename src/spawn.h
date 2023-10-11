#ifndef __UVMTD_SPAWN_H__
#define __UVMTD_SPAWN_H__

typedef int (daemonf)(void*);

void spawn(char *, daemonf *, void *);

#endif /* __UVMTD_SPAWN_H__ */
