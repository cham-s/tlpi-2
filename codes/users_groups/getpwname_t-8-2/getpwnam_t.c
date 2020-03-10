#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <string.h>
#include "tlpi_hdr.h"

struct passwd *m_getpwnam(const char *name) {
	struct passwd *entry;

	if (*name == '\0' || name == NULL)
	{
		errno = ENOENT;
		return NULL;
	}

	entry = getpwent();
	while( entry != NULL)
	{
		if (strcmp(entry->pw_name, name) == 0)
			break;
		entry = getpwent();
	}

	setpwent();
	endpwent();

	return entry;
}

int
main(int argc, char *argv[])
{
	struct passwd *user;

	user = m_getpwnam("kata");

	if (user != NULL)
		printf("name: %s\n", user->pw_name);
	else
		printf("something bad happened\n");

	exit(EXIT_SUCCESS);
}
