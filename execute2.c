#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(char **args)
{
	int (*builtin)(char **args);

	if (args[0] == NULL)
		return (1);

	builtin = get_builtin(args[0]);

	if (builtin != NULL)
		return (builtin(args));

	return (execute(args));
}
