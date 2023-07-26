#include "shell.h"

/**
 * _strdup - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char *str, const char *delim)
{
	static char *last_token; /* Keep track of the last token*/
	char *token; /* Store the token to be returned*/
	int i, j;

	/* If str is NULL, start from the last token*/
	if (str == NULL)
		str = last_token;

	/* If str is empty, return NULL*/
	if (*str == '\0')
		return (NULL);

	/* Find the start of the token*/
	i = 0;
	while (str[i] != '\0')
	{
		if (strchr(delim, str[i]) == NULL)
			break;
		i++;
	}

	/* Find the end of the token*/
	j = i + 1;
	while (str[j] != '\0')
	{
		if (strchr(delim, str[j]) != NULL)
			break;
		j++;
	}

	token = (char *)malloc(j - i + 1);
	if (token == NULL)
		return (NULL);

	strncpy(token, str + i, j - i);
	token[j - i] = '\0';
	last_token = str + j;

	return (token);
}

/**
 * rev_string - reverses a string.
 * @s: input string.
 * Return: no return.
 */
void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
