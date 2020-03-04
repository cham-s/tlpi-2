#include <stdlib.h>
#include <stdio.h>

// Testing free on env pointers
extern char **environ;

int main(int ac, char **av)
{
	size_t i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		free(environ[i]);
		i += 1;
	}
	return 0;
}
