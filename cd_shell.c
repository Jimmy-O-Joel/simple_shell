#include "shell.h"

#include "shell.h"

/**
 * cd_shell - changes current directory
 *
 * @args: arguments
 * @_environ: env variables
 * Return: 1 on success
 */
int cd_shell(char **args, char **_environ)
{
	char *dir;
	int ishome, ishome2, isddash, isdotdot;

	dir = args[1];

	if (dir == NULL)
	{
		cd_home(_environ);
		return (1);
	}
	ishome = _strcmp("$HOME", dir);
	ishome2 = _strcmp("~", dir);
	isddash = _strcmp("--", dir);
	isdotdot = _strcmp("..", dir);

	if (!ishome || !ishome2 || !isddash)
	{
		/* Handle special cases: cd ~, cd $HOME, cd -- */
		cd_home(_environ);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(_environ);
		return (1);
	}

	if (isdotdot)
	{
		cd_dotdot(_environ);
		return (1);
	}

	if (_strcmp(".", dir) == 0)
	{
		return (1);
	}
	cd_to(dir, _environ);
	return (1);
}

