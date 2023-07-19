#include "shell.h"


/**
 * cd_shell - change to another directory
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int cd_shell(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	}
	else if (chdir(args[1]) != 0)
	{
		perror("lsh");
	}

	return (1);
}
