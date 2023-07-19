#include "shell.h"

/**
*prompt - UNIX interprator
*
*Return: void
*/

void prompt(void)
{
	const char *prompt = "$";
	ssize_t count = 0;
	char * line;
	char **args;
	int status;


	do
	{
		count = write (1, prompt, strlen(prompt));
		if (count == -1)
		{
			perror("Error writing to stdout");
			exit(1);
		}

		line = read_line();
		args = parser(line);
		status = execute(args);

		free(line);
		free(args);
	}while (status);
}
