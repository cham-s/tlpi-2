#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int
main(int argc, char **argv)
{
	int input_fd, output_fd, open_flags;
	mode_t file_perms;
	ssize_t numread;
	char buf[BUF_SIZE];

	if (argc != 3 || strcmp(argv[1], "--help") == 0)
		usageErr("%s old-file new-file\n", argv[0]);

	/* Open input and output files */

	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
		errExit("opening file %s", argv[1]);

	open_flags = O_CREAT | O_WRONLY | O_TRUNC;
	file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	
	output_fd = open(argv[2], open_flags, file_perms);

	if (output_fd == - 1)
		errExit("opening file %s", argv[2]);

	/* Transfer data until we encounter end of input or an error */

	while ((numread = read(input_fd, buf, BUF_SIZE)) > 0)
		if (write(output_fd, buf, numread) != numread)
			fatal("couldn't write the whole buffer");
	if (numread == -1)
		errExit("read");
	if (close(input_fd) == -1)
		errExit("close input");
	if (close(output_fd) == -1)
		errExit("close output");
	exit(EXIT_SUCCESS);
}
