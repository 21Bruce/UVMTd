#include "daemon_linmap.h"
#include "elib.h"

#include <sys/mman.h>
#include <unistd.h>

#define ERR_MEM_STAT 65
#define ERR_INT_STAT 66

typedef unsigned char byte;

/*
 * The linear map daemon maps in a
 * configurable amount of memory,
 * stores values in it, sleeps for a
 * configurable amount of time,
 * and checks that the memory is the same
 * and then frees the memory.
 */
int
daemon_linmap(void *config)
{
	/*
	 * Get system page size.
	 */
	long pgsize = sysconf(_SC_PAGESIZE);

	/*
	 * Check daemon conf and set defaults. 
	 */	
	struct daemon_linmap_conf conf = config;
	unsigned int sleept = conf.sleept > 0 ? conf.sleept : 60;
	unsigned int npages = conf.npages > 0 ? conf.npages : 1;

	/*
	 * Main loop of the daemon 
	 */	
	byte *map; 
	for (; ; ;) {

		/*
		 * Allocate map or die. 
		 */
		map = mmap(NULL, npages * pgsize, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
		if (map == NULL) {
			derr("Could not map memory");
			return ERR_MEM_STAT;
		}

		/*
		 * Store and check memory in the map. 
		 */
		for (int i = 0; i < npages * pgsize; i++)
			map[i] = (byte)i;

		/*
		 * Sleep and hold memory.
		 */
		sleep(sleept);

		for (int i = 0; i < npages * pgsize; i++) {
			if (map[i] != (byte)i) {
				derr("Integrity failure, expected %d at %p, but got %d", (byte)i, (map + i), map[i]);
				return ERR_INT_STAT;
			}
		}

		/*
		 * Release memory.
		 */
		munmap(map, npages * pgsize);
	}
	/*
	 * NOT REACHED.
	 */
	return 0;
}
