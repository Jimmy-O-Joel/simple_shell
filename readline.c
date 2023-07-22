#include "shell.h"

/**
*read_line - function that reads a line from the user
*
*Return:pointer to a string with line content
*/

char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;
	ssize_t chars_read;

	chars_read = _getline(&line, &buffer_size, stdin);

	if (chars_read == -1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			perror("Error while reading input");
			exit(EXIT_FAILURE);
		}
	}

	line[strcspn(line, "\n")] = '\0';

	return (line);
}
