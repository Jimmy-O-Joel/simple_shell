#include "shell.h"

/* Built-in command names and corresponding functions */

const char *builtin_str[] = {"cd","exit","help"};

int (*builtin_func[]) (char **) = {
    &cd_shell,
    &exit_shell
};

/**
*execute - function that executes commands
*@args:array of argument strings
*Return:
*/

int execute(char **args)
{

	int i;
	int equal;
	path(args); /*searches in path for an exe */
    if (args[0] == NULL)
    {
        return 1;  /* Empty command */
    }

    for (i = 0; i < sizeof(builtin_str) / sizeof(char *); i++)
    {
        if (strcmp(builtin_str[i], args[0]) == 0)
        {
            return (*builtin_func[i])(args);
        }

    }

    return launch_shell(args);
}
