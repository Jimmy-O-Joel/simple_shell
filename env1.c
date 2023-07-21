#include "shell.h"

/**
 * copy_info - copies info to create a new env or alias
 * @name: name
 * @value: value
 *
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the env variable
 * @_environ: env variable
 * Return: 1 on success, -1 on failure
 */
int set_env(const char *name, const char *value, char **_environ)
{
    char *new_env_var;
    char *var_env;
    size_t name_len, value_len;
    int i;

    if (name == NULL || value == NULL)
    {
        // Invalid arguments, return failure
        return -1;
    }

    name_len = strlen(name);
    value_len = strlen(value);

    // Allocate memory for the new environment variable
    new_env_var = malloc(name_len + value_len + 2);
    if (new_env_var == NULL)
    {
        perror("malloc");
        return -1;
    }

    // Create the new environment variable string: name=value\0
    snprintf(new_env_var, name_len + value_len + 2, "%s=%s", name, value);

    // Find if the environment variable already exists
    for (i = 0; _environ[i] != NULL; i++)
    {
        var_env = _environ[i];

        if (strncmp(var_env, name, name_len) == 0 && var_env[name_len] == '=')
        {
            // Update the existing environment variable
            free(_environ[i]);
            _environ[i] = new_env_var;
            return 1;
        }
    }

    // If the environment variable does not exist, add it to the environment
    _environ[i] = new_env_var;
    _environ[i + 1] = NULL;

    return 1;
}


/**
 * _setenv - compares env variables names with the name passed.
 * @args: arguments
 *
 * Return: 1 on success.
 */
int _setenv(char **args, char **_environ)
{

	if (args[1] == NULL || args[2] == NULL)
	{
		/*get error function goes here*/
		return (1);
	}

	set_env(args[1], args[2], _environ);

	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @args: args
 *@_environ:env variable
 *
 * Return: 1 on success.
 */
int _unsetenv(char **args, char **_environ)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (args[1] == NULL)
	{
		/* error function goes here*/
		return (1);
	}
	k = -1;
	for (i = 0; _environ[i]; i++)
	{
		var_env = _strdup(_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		/* error function goes here */
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; _environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = _environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(_environ[k]);
	free(_environ);
	_environ = realloc_environ;
	return (1);
}
