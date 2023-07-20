#include "shell.h"

/**
 * _getline - function that reads a line from a file stream
 * @lineptr: pointer to the pointer that stores the line of text
 * @n: buffer size pointed to by lineptr
 * @stream: input stream where the function reads the line of text from
 * Return: number of characters read, -1 if an error occurs or EOF is reached
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	if (*lineptr == NULL || n == NULL || stream == NULL)
	{
		return (-1);
	}

	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}

	return (read_characters(lineptr, n, stream));
}
/**
 * read_characters - Helper function to read characters from the stream.
 * @lineptr: A pointer to the pointer that stores the line of text.
 * @n: A pointer to the buffer size pointed to by 'lineptr'.
 * @stream: The input stream where the function reads the characters from.
 * Return: The number of characters read (excluding the null terminator),
 *         -1 if an error occurs or if EOF is reached.
 */

static ssize_t read_characters(char **lineptr, size_t *n, FILE *stream)
{
	size_t index = 0;
	int i;

	while (1)
	{
		i = fgetc(stream);
		if (i == EOF)
		{
			if (index == 0)
			{
				return (-1);
			}
			break;
		}
		(*lineptr)[index] = (char)i;
		index++;

		if (index >= *n)
		{
			resize_buffer(lineptr, n);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		if (i == '\n')
		{
			break;
		}
	}
	(*lineptr)[index] = '\0';
	return (index);
}

/**
 * resize_buffer - helper function to resize the buffer
 * @lineptr: A pointer to the pointer that stores the line of text.
 * @n: A pointer to the buffer size pointed to by lineptr.
 */

static void resize_buffer(char **lineptr, size_t *n)
{
	char *new_lineptr;

	*n *= 2;
	new_lineptr = (char *)realloc(*lineptr, *n);

	if (new_lineptr != NULL)
	{
		*lineptr = new_lineptr;
	}
}

