#include "elib.h"
#include "daemonize.h"
#include "daemone_linmap.h"

int
main(int argc, char *argv[])
{
	struct daemon_linmap_conf conf = {
		0,
		10
	};
	spawn("LINMAPd", daemon_linmap, (void *)conf);
return 0;
}
