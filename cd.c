#include "shell.h"


/**
 * cd_to - changes to a directory given by the user.
 *
 * @dir: directory to change to
 * @_environ: environment variables
 * Return: no return
 */
void cd_to(const char *dir, char **_environ)
{
	char pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("cd");
		return;
	}

	if (chdir(dir) == -1)
	{
		/* Handle the case when the directory does not exist or is inaccessible */
		perror("cd");
		return;
	}

	/* Update the environment variables PWD and OLDPWD */
	set_env("OLDPWD", pwd, _environ);
	set_env("PWD", dir, _environ);
}



/**
 * cd_previous - changes the current directory to the previous directory.
 *
 * @_environ: environ
 * Return: no return
 */
void cd_previous(char **_environ)
{
	char *oldpwd = _getenv("OLDPWD", _environ);

	if (oldpwd != NULL)
	{
		cd_to(oldpwd, _environ);
	}
	else
	{
		/* Handle the case when OLDPWD environment variable is not set*/
		fprintf(stderr, "cd: OLDPWD not set\n");
	}
}


/**
 * cd_home - changes the current directory to the user's home directory.
 *
 * @_environ: environ
 * Return: no return
 */
void cd_home(char **_environ)
{
	char *home_dir = _getenv("HOME", _environ);

	if (home_dir != NULL)
	{
		cd_to(home_dir, _environ);
	}
	else
	{
		/* Handle the case when HOME environment variable is not set*/
		fprintf(stderr, "cd: HOME not set\n");
	}
}

/**
 * cd_dotdot - changes the current directory to the parent directory.
 *
 * @_environ: environ
 * Return: no return
 */
void cd_dotdot(char **_environ)
{
	char *pwd = _getenv("PWD", _environ);
	char *parent_dir = NULL;

	if (pwd != NULL)
	{
		char *last_slash = strrchr(pwd, '/');

		if (last_slash != NULL)
		{
			/* Truncate the PWD to the parent directory path*/
			*last_slash = '\0';
			parent_dir = pwd;
		}
		else
		{
			/*Handle the case when PWD does not have a parent directory*/
			fprintf(stderr, "cd: Already at root directory\n");
		}
	}
	else
	{
		/* Handle the case when PWD environment variable is not set*/
		fprintf(stderr, "cd: PWD not set\n");
	}

	if (parent_dir != NULL)
	{
		cd_to(parent_dir, _environ);
	}
}
