#include "tlpi_hdr.h"
#include <string.h>

static size_t size_array(char **array)
{
	size_t i;

	i = 0;

	while (array[i] != NULL)
		i += 1;

	return i;
}

static Boolean is_there(char **array, char *name)
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

static void print_array(char **array)
{
	size_t i;

	i = 0;

	while (array[i] != NULL)
	{
		printf("%s\n", array[i]);
		i += 1;
	}
}

char **append_env(char **env, char *value)
{
	int i;
	size_t len;
	size_t len_array;
	char **new_array;
	char *entry;

	len = 0;
	len_array = size_array(env);
	i = 0;

	printf("size array\n");
	new_array = (char **)malloc(sizeof(char *) * (len_array + 1));

	if (new_array == NULL)
		errExit("error malloc");

	while (env[i] != NULL)
	{
		len = strlen(env[i]);
		entry = (char *)malloc(sizeof(char)  * len);
		strcpy(entry, env[i]);

		if (entry == NULL)
			fatal("malloc failed at append_env() while setting entry");

		new_array[i] = entry;
		i += 1;
	}
	new_array[i] = value;
	i++;
	new_array[i] = NULL;

	return new_array;
}


int m_setenv(const char *name, const char *value, int overwrite);
{
	char *complete_name;
	size_t size_name;
	size_t size_value;

	if getenv(name == NULL)
	{
		size_name = strlen(name);
		size_value = strlen(value);
		complete_name = (char *)malloc(sizeof(char) * (size_name + size_value
						+ 2));
		strncpy(complete_name, name, size_name);
		complete_name[size_name] = '=';
		strncpy(complete_name + (size_name + 1), value, size_value);
		complete_name[size_name + size_value + 1] = '\0';

		putenv()
	}
}

int main(int argc, char *argv[], char **env)
{
	char **new_env;

	printf("[DEBUG] env before:\n");
	print_array(env);
	new_env = append_env(env, "NEW=Value");
	printf("[DEBUG] env after:\n");
	print_array(new_env);

	exit(EXIT_SUCCESS);
}
