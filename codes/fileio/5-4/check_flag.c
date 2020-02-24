#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
	int newfd, flags1, flags2;

	newd = dup(1);

	flags1 = fcntl(1, F_GETFL);
	flags2 = fcntl(newfd, F_GETFL);

	if (flags1 == flags2)
		printf("They share the same flags\n");
	else
		printf("They don't share the same flags");

	return 
}
