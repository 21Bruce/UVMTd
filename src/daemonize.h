#ifndef __UVMTD_DAEMONIZE_H__
#define __UVMTD_DAEMONIZE_H__

typedef void(*daemonf)(void);

void spawn(char *, daemonf);

#endif /* __UVMTD_DAEMONIZE_H__ */
