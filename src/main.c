#include "elib.h"
#include "spawn.h"
#include "daemon_linmap.h"

int
main(int argc, char *argv[])
{
	struct daemon_linmap_conf conf = {
		(24 * 60),
		100000,
	};
	spawn("LINMAPd", daemon_linmap, (void *)&conf);
	return 0;
}
