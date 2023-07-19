#include "shell.h"

/**
*_getline - function that reads a line from a file stream
*@lineptr:pointer to the pointer that stores the line of text
*@n:buffer size pointed to by lineptr
*@stream:input stream where the function reads the line of text from
*Return: number of characters read, -1 if an error occurs or EOF is reached
*/

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	size_t index = 0
	int i;
	char *new_lineptr;

	if (*lineptr == NULL || n == NULL ||stream == NULL)
	{
		return (-1)
	}
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = (char *)malloc(*n);
		if(*lineptr == NULL)
		{
			return (-1);
		}
	}
	while (1)
	{
		i = fgetc(stream);
		if (i == EOF)
		{
			if (index == 0)
			{
				return (-1)
			}
			break;
		}
		(*lineptr)[index] = (char)i;
		index ++;
		
		if (index >= *n)
		{
			*n *=2;
			new_lineptr = (char*)realloc(*lineptr, *n);
			if (new_ptr == NULL)
			{
				return (-1);
			}
			*lineptr = new_lineptr;
		}
		if (i == '\n')
		{
			break;
		}
	}
	(*lineptr)[index] = '\0';
	return (index);
}
