#include "shell.h"

/**
 * get_builtin - builtin for the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(char **)
{
	builtin_t builtin[] = {
		{"exit", exit_shell},
		{"cd", cd_shell}
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}
