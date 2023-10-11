#include "elib.h"
#include "spawn.h"
#include "daemon_linmap.h"
#include "daemon_pgalign.h"

int
main(int argc, char *argv[])
{
	struct daemon_pgalign_conf pg_conf = {
	 	0,	
		0,
	};
	struct daemon_linmap_conf lm_conf = {
	 	0,	
		0,
	};
	spawn("PGALIGNd", daemon_pgalign, (void *)&pg_conf);
	spawn("LINMAPd", daemon_linmap, (void *)&lm_conf);
	return 0;
}
