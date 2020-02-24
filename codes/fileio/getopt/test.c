#include <ctype.h>
#include "tlpi_hdr.h"

#define printable(ch) (isprint((unsigned char) ch) ? ch : '#')

static void
usageError(char *progName, char *msg, int opt)
{
	if (msg != NULL && opt != 0)
		fprintf(stderr, "%s (-%c)\n", msg, printable(opt));
	fprintf(stderr, "Usage: %s [-p arg] [-x]\n", progName);
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	int opt, xfnd, nfnd;
	char *pstr;
	char *nstr;

	xfnd  = 0;
	pstr = NULL;

	while ((opt = getopt(argc, argv, ":p:xn:")) != -1) {
		printf("opt =%3d (%c); optind = %d", opt, printable(opt), optind);
		if (opt == '?' || opt == ':')
			printf("; optopt =%3d (%c)", optopt, printable(optopt));
		printf("\n");

		switch (opt) {
			case 'p': pstr = optarg;		break;
			case 'n': nstr = optarg;		break;
			case 'x': xfnd++;				break;
			case ':': usageError(argv[0], "Missing argument", optopt);
			case '?': usageError(argv[0], "Unrecognize option", optopt);
			default: fatal("Unexpected case in switch()");
		}

	}

	if (xfnd != 0)
		printf("-x was specified (count=%d)\n", xfnd);
	if (pstr != NULL)
		printf("-p was specified with the value \"%s\"\n", pstr);
	if (optind < argc)
		printf("First nonoption argument is \"%s\" at argv[%d]\n",
			   	argv[optind], optind);
	exit(EXIT_SUCCESS);
}
