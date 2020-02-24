#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char **argv)
{
	int fd, open_flags;
	mode_t file_perms;
	size_t len;
	char *bytes;

	if (argc < 3 || argc > 4 || strcmp(argv[1], "--help") == 0)
	{
		if(strcmp(argv[3], "x") != 0)
			usageErr("%s filename num-bytes [x]\n", argv[0]);
	}

	len = getLong(argv[2], GN_ANY_BASE, argv[2]);
	printf("[DEBUG] %ld nbytes\n", len);

	if (argc == 4)
	{
		if (argv[3][0] == 'x')
			open_flags = O_CREAT | O_WRONLY;
		else
			open_flags = O_CREAT | O_WRONLY | O_APPEND;
	}
	else
		open_flags = O_CREAT | O_WRONLY | O_APPEND;

	file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	fd = open(argv[1], open_flags, file_perms);

	if(fd == -1)
		errExit("open");

	bytes = malloc(sizeof(char) * len);
	if (bytes == NULL)
		errExit("malloc");
	printf("[DEBUG] allocateed  %ld nbytes\n", len);
	for (int i = 0; i < len; i++)
		bytes[i] = 'a';

	for (int i = 0; i < len; i++)
	{
		if (argc == 4)
		{
			if (argv[3][0] == 'x')
			{
				if (lseek(fd, 0, SEEK_END) == -1)
					errExit("lseek");
				if (write(fd, &bytes[i], 1) == -1)
					errExit("write");
			}
			else
				if (write(fd, &bytes[i], 1) == -1)
					errExit("write");
		}
		else
			if (write(fd, &bytes[i], 1) == -1)
				errExit("write here");
	}

	if (close(fd) == -1)
		errExit("close output");

	free(bytes);
	exit(EXIT_SUCCESS);
}
