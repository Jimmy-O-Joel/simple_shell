#include "shell.h"

/**
*path - searches in $PATH for an executable command
*@args:array of argument strings
*Return:0 on success, 1 on failure
*/

int path(char **args)
{

    /* REtriving path directory using getenv */
	char *path;
	char *token;
	char command_path[100];

	path = getenv("PATH");

	/* tokenize the path variale to otain individual directory paths */

	token = strtok(path, ":");
	while (token != NULL)
	{
		strcpy(command_path, token);
		strcat(command_path, "/");
		strcat(command_path, args[0]);

		/* check if the command exists and is executable */

			if (access(command_path, X_OK) == 0)
			{
				/* execute the command using execvp */
				args[0] = command_path;
				if (execvp(args[0], args) == -1)
				{
					perror("execvp");
					return (1);
				}
			}

		/* get the next directory path token */
		token = strtok(NULL, ":");
	}
	/* print error message using perror */
	perror("command not found");
	return (1);

}
