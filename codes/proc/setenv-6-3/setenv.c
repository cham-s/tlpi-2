#include "tlpi_hdr.h"
#include <string.h>

extern char **environ;

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
			errExit("malloc failed at append_env() while setting up entry");

		new_array[i] = entry;
		i += 1;
	}
	new_array[i] = value;
	i++;
	new_array[i] = NULL;

	return new_array;
}

size_t index_of(const char *name, char **array)
{
	size_t i;
	size_t len;

	len = strlen(name);

	i = 0;

	while (array[i] != NULL)
	{
		if (strncmp(array[i], name, len) == 0)
			return i;
		i += 1;
	}

	return -1;
}

void update_name(const char *name, char *complete_name)
{
	size_t i;
	size_t len;

	i = 0;
	len = strlen(name);

	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, len) == 0)
		{
			environ[i] = complete_name;
			break;
		}
		i += 1;
	}
}

// get a duplicate environ without the one mentioned in name
char **delete_name(const char *name)
{
	size_t env_len;
	size_t index;
	size_t i;
	size_t env_i;
	size_t str_len;
	char **new_env;
	char *duplicate;

	i = 0;
	env_i = 0;
	env_len = size_array(environ);
	index = index_of(name, environ);

	new_env = (char **)malloc(sizeof(char *) * env_len);

	if (new_env == NULL)
		return NULL;

	while (environ[i] != NULL)
	{
		if (i == index)
		{
			i += 1;
			continue;
		}
		str_len = strlen(environ[i]);
		duplicate = (char *)malloc(sizeof(char) * str_len);

		if (duplicate == NULL)
			return NULL;

		new_env[env_i] = strcpy(duplicate, environ[i]);

		env_i += 1;
		i += 1;
	}
	new_env[env_i] = NULL;

	return new_env;
}


int m_setenv(const char *name, const char *value, int overwrite)
{
	char *complete_name;
	size_t size_name;
	size_t size_value;
	char *getenv_pointer;

	getenv_pointer = getenv(name);

	if (getenv_pointer != NULL && overwrite == 0)
		return 0;

	size_name = strlen(name);
	size_value = strlen(value);
	complete_name = (char *)malloc(sizeof(char) * (size_name + size_value
					+ 2));
	strncpy(complete_name, name, size_name);
	complete_name[size_name] = '=';
	strncpy(complete_name + (size_name + 1), value, size_value);
	complete_name[size_name + size_value + 1] = '\0';

	if (getenv_pointer == NULL)
	{
		printf("\n\nCase Not Present\n\n");
		if (putenv(complete_name) != 0)
			errExit("error putenv() %s", complete_name);
		return 0;
	}
	else if (overwrite != 0)
	{
		printf("\nCase Update\n");
		update_name(name, complete_name);
	}

	return 0;
}

int m_unsetenv(const char *name)
{
	size_t len;
	char **tmp;

	if (getenv(name) == NULL)
		return 0;

	tmp = delete_name(name);

	if (tmp == NULL)
		return -1;

	environ = tmp;
	return 0;
}

int main(int argc, char *argv[])
{
	size_t count;


	// setenv tests
	printf("Fresh env:\n\n");
	print_array(environ);
	count = size_array(environ);
	printf("\nsize: %zu\n", count);

	printf("\nAdding GREET=Bonjour:\n\n");
	m_setenv("GREET", "Bonjour", 0);
	print_array(environ);
	count = size_array(environ);
	printf("\nsize: %zu\n", count);

	printf("\nSet env with overwrite 0 GREET=Hola:\n\n");
	m_setenv("GREET", "Hola", 0);
	print_array(environ);
	count = size_array(environ);
	printf("\nsize: %zu\n", count);

	printf("\nSet env with overwrite 1 GREET=Hola:\n\n");
	m_setenv("GREET", "Hola", 1);
	print_array(environ);
	count = size_array(environ);
	printf("\nsize: %zu\n", count);

	// unsetenv test
	printf("\nUnset env removing invalid name HELLO:\n\n");
	m_unsetenv("HELLO");
	print_array(environ);
	count = size_array(environ);
	printf("\nsize: %zu\n", count);

	printf("\nUnset env removing valid name GREET:\n\n");
	m_unsetenv("GREET");
	print_array(environ);
	count = size_array(environ);
	printf("\nsize: %zu\n", count);

	return 0;
}
