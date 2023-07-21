#include "shell.h"

/* Built-in command names and corresponding functions */

const char *builtin_str[] = {"cd","exit","env"};

int (*builtin_func[]) (char **args, char **_environ) = {
    &cd_shell,
    &exit_shell,
    &_env
};

/**
*execute - function that executes commands
*@args:array of argument strings
*Return:
*/

int execute(char **args, char **_environ)
{

	int i;
	int equal;
    if (args[0] == NULL)
    {
        return 1;  /* Empty command */
    }
    for (i = 0; i < sizeof(builtin_str) / sizeof(char *); i++)
    {
        if (strcmp(builtin_str[i], args[0]) == 0)
        {
            return (*builtin_func[i])(args, _environ);
        }

    }

    return launch_shell(args);
}
