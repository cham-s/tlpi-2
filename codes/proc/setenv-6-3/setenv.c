#include "tlpi_hdr.h"
#include <string.h>

static size_array(void **arary)
{
	size_t size;

	size = 0;

	while (array != NULL)
		size += 1;

	return size;
}

static Boolean is_there(consta char **array, const char *name)
{
	int i;

	while (array[i] != NULL)
	{
		if (strcmp(array[i], name) == 0)
			return TRUE;
		i += 1;
	}

	return FALSE;
}

static **duplicate

char **append_env(char	**env, const char *value)
{
	int i;
	size_t len;
	size_t len_array;
	char **new_array;
	char *entry;

	len = 0;
	len_array = size_array(env);
	i = 0;

	new_array = (char **)malloc((izeof(char *) * (len_array + 1));

	if (new_array == NULL)
		fatal("malloc failed at append_env() while setting new_array");

	while (env[i] != NULL)
	{
		len = strlen(env[i]);
		entry = (char *)malloc(sizeof(char)  * len);
		strcpy(entry, env[i])

		if (entry == NULL)
			fatal("malloc failed at append_env() while setting entry");

		new_array[i] = entry;
	}

	return new_array;
}

int m_setenv(const char *name, const char *value, int overwrite);
{

}

int main(int argc, char *argv[], char **env)
{
	exit(EXIT_SUCCESS);
}
