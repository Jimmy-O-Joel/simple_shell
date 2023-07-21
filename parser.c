#include "shell.h"

/**
*parser - parse an array of string into individual tokens
*@line:array of string to be tokenized
*
*Return: pointer to an array
*/
char **parser(char *line)
{

	int buf_size = TOK_BUFSIZE;
	int i = 0;
	char **token_holder;
	char *token;

	token_holder = (char **)malloc(buf_size * sizeof(char *));
	if (token_holder == NULL)
	{
		return (NULL);
	}

	token = _strtok(line, " ");
	while (token != NULL)
	{
		token_holder[i] = token;
		i++;
		if (i >= buf_size)
		{
			buf_size += buf_size;
			token_holder = realloc(token_holder, buf_size * sizeof(char *));
			if (token_holder == NULL)
			{
				return (NULL);
			}
		}
		token = _strtok(NULL, " ");
	}

	token_holder[i] = NULL;
	return (token_holder);
}
