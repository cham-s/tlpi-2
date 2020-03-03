#include <stdlib.h>
#include <stdio.h>

// Testing free on env pointers

int main(int ac, char **av, char **env)
{
	size_t i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		free(env[i]);
		i += 1;
	}
	return 0;
}
