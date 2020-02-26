#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

size_t m_readv(int fd, const struct iovec *iov, int iovcnt)
{
	size_t num_read;
	size_t total_read;

	total_read = 0;

	if (fcntl(fd, F_SETFL, O_APPEND) == -1)
		errExit("fcntl O_APPEND in m_readv");

	for (int i=0; i<iovcnt; i++)
	{
		num_read = read(fd, iov[i].iov_base, iov[i].iov_len);
		if (num_read == -1)
			return -1;
		total_read += num_read;
	}

	return total_read;
}

size_t m_writev(int fd, const struct iovec *iov, int iovcnt)
{
	size_t num_written;
	size_t total_write;
	size_t total_iov_len;
	size_t start;
	char *buf;

	total_iov_len = 0;
	start = 0;

	if (fcntl(fd, F_SETFL, O_APPEND) == -1)
		errExit("fcntl O_APPEND in m_writev");

	for (int i=0; i<iovcnt; i++)
		total_iov_len += iov[i].iov_len;

	buf = malloc(sizeof(char) * total_iov_len);
	if (buf == NULL)
		fatal("error malloc NULL");

	for (int i=0; i<iovcnt; i++)
	{
		memcpy(buf + start, iov[i].iov_base, iov[i].iov_len);
		start += iov[i].iov_len;
	}

	num_written = write(fd, buf, total_iov_len);
	if (num_written == -1)
		return -1;

	free(buf);
	return num_written;
}

int
main(int argc, char *argv[])
{
	/* int fd;
	struct iovec iov[3];
	struct stat myStruct;
	int x;
#define STR_SIZE 100
	char str[STR_SIZE];
	ssize_t numRead, totRequired;

	if (argc !=2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s file\n", argv[0]);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		errExit("open");

	totRequired = 0;

	iov[0].iov_base = &x;
	iov[0].iov_len = sizeof(x);
	totRequired += iov[0].iov_len;

	iov[1].iov_base = &myStruct;
	iov[1].iov_len = sizeof(myStruct);
	totRequired += iov[1].iov_len;

	iov[2].iov_base = str;
	iov[2].iov_len = STR_SIZE;
	totRequired += iov[2].iov_len;

	numRead = m_readv(fd, iov, 3);
	if (numRead == -1)
		errExit("readv");

	if (numRead < totRequired)
		printf("Read fewer bytes than requested\n");

	printf("total bytes request: %ld; bytes read: %ld\n",
	(long) totRequired, (long) numRead);
	*/

	char *str0 = "hello ";
	char *str1 = "world\n";
	struct iovec iov2[2];
	ssize_t nwritten;

	iov2[0].iov_base = str0;
	iov2[0].iov_len = strlen(str0);
	iov2[1].iov_base = str1;
	iov2[1].iov_len = strlen(str1);
	nwritten = m_writev(STDOUT_FILENO, iov2, 2);
	exit(EXIT_SUCCESS);
}
