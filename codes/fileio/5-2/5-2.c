#include <sys/wait.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int fd;
	pid_t f;

	if (argc !=2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s file\n", argv[0]);

	fd = open(argv[1], O_WRONLY, O_APPEND);
	if (fd == -1)
		errExit("open");

	if (lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");
	if (write(fd, "ta", 2) == -1)
		errExit("write");
	if ((f = fork()) == 0)
	{
		int fd2;
		fd2 = open(argv[1], O_WRONLY, O_APPEND);
		if (fd2 == -1)
			errExit("open");

		if (lseek(fd2, 0, SEEK_SET) == -1)
			errExit("lseek");
		if (write(fd2, "bila", 4) == -1)
			errExit("write");
	} else {
		int status = -18;
		sleep(10);
		wait(&status);
		if (close(fd) == -1)
			errExit("close parent");
		printf("status: %d\n", status);
	}

	exit(EXIT_SUCCESS);
}


