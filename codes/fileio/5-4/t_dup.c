#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int m_dup(int oldfd)
{
	int newfd;

	newfd = fcntl(oldfd, F_DUPFD);

	return (newfd);
}

int m_dup2(int oldfd, int newfd)
{
	if (fcntl(oldfd, F_GETFL) == - 1)
	{
		errno = EBADF;
		return -1;
	}

	if (oldfd == newfd)
		return oldfd;

	if (fcntl(1, F_GETFD) != -1)
		if (close(newfd) == -1)
			errExit("close in m_dup2");

	newfd = fcntl(oldfd, F_DUPFD, newfd);
	return newfd;
}

int
main(int argc, char **argv)
{
	int newfd;
	write(2, "Error1\n", 7);

	newfd = m_dup2(120, 2);
	if (newfd == -1)
		errExit("m_dup");
	write(2, "Error2\n", 7);

	exit(EXIT_SUCCESS);
}
