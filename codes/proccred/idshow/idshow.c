#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <limits.h>
#include <sys/fsuid.h>
#include "ugid_functions.h"
#include "tlpi_hdr.h"

#define SG_SIZE (NGROUBPS_MAX + 1)

int
main(int argc, char *argv[])
{
	uid_t ruid, euid, suid, fsuid;
	gid_t rgid, egid, sgid, fsgid;
	gid_t suppGroups[SG_SIZE];
	int numGroups, j;
	char *p;

	if (getresuid(&ruid, &euid, &suid) == -1)
		errExit();

	exit(EXIT_SUCCESS);
}


