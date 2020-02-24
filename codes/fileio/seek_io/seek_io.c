#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char **argv)
{
	size_t len;
	len = getLong(argv[1], GN_ANY_BASE, argv[1]);
	printf("len: %ld\n", len);

	exit(EXIT_SUCCESS);
}
