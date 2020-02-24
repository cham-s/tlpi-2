#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "tlpi_hdr.h"

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

static void usageError(char *progName, char *msg, int opt)
{
	if (msg != NULL && opt != 0)
		fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
	fprintf(stderr, "Usage: %s [-a] filename\n", progName);
	exit(EXIT_FAILURE);
}

int
hasOption(int argc, char *argv[])
{
	int opt, afnd;

	afnd  = 0;

	while ((opt = getopt(argc, argv, ":a")) != -1) {
		switch (opt) {
			case 'a': afnd = 1;		break;
			case ':': usageError(argv[0], "Missing argument", optopt);
			case '?': usageError(argv[0], "Unrecognize option", optopt);
			default: fatal("Unexpected case in switch()");
		}
	}

	return afnd;
}

int
main(int argc, char *argv[])
{
	int output_fd, open_flags, has_option;
	char *filename;
	ssize_t numread;
	char buf[BUF_SIZE];

	if (argc < 2 || argc > 3)
		usageErr("%s [-a] filename\n", argv[0]);

	has_option = hasOption(argc, argv);
	filename = argv[optind];

	if (has_option)
		open_flags = O_APPEND | O_WRONLY | O_CREAT;
	else
		open_flags = O_CREAT | O_WRONLY | O_TRUNC;

	output_fd = open(filename, open_flags);

	if (output_fd == -1)
		errExit("opening file %s", filename);

	while ((numread = read(0, buf, BUF_SIZE)) > 0)
	{
		if (write(output_fd, buf, numread) != numread)
			fatal("couldn't write the whole buffer");
		if (write(1, buf, numread) != numread)
			fatal("couldn't write the whole buffer");
	}
	if (numread == -1)
		errExit("read");
	if (close(output_fd) == -1)
		errExit("close output");
	exit(EXIT_SUCCESS);
}
