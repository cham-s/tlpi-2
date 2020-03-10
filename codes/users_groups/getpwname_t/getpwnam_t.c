#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include "tlpi_hdr.h"

int
main(int argc, char *argv[])
{
	struct passwd *entry;

	entry = getpwent();
	while( entry != NULL)
	{
		printf("name: %s\nhome directory: %s\nshell: %s\n",
				entry->pw_name, entry->pw_dir, entry->pw_shell);
		entry = getpwent();
	}

	setpwent();
	endpwent();

	exit(EXIT_SUCCESS);
}
