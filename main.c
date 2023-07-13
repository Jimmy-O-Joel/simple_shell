//main.c
#include "shell.h"

/**
*main - entry point of our program
*
*Return: Always 0
*/


int main(void)
{
	Prompt();
	return (0);

}


//prompt.c	
/**
*prompt - UNIX interprator
*
*Return: void
*/

void prompt(void)
{
	const char *prompt = "$"
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
		args = parser (line);
		status = execute (args);

		free(line);
		free(args);
	}while (status);
}

//read_line.c

/**
*read_line - function that reads a line from the user
*
*@Return:pointer to a string with line content
*/

char *read_line(void)
{
	char *line = NULL;
	size_t buffer_size = 0;
	ssize_t chars_read;
	
	chars_read = getline(&line, &buffer_size, stdin);

	if (chars_read == - 1)
	{
		if (feof(stdin))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			free(line);
			perror ("Error while reading input");
			exit(EXIT_FAILURE);
		}
	}

	return(line);
}

//parser.c

/**
*parser - parse an array of string into individual tokens
*@line:array of string to be tokenized
*
*@Return: pointer to an array
*/
char **parser(char *line)

	int buffer_size = 1024;
	int i = 0;
	char **token_holder;
	char *token;
	
	token_holder = (char**)malloc(buffer_size * sizeof(char *));
	if (token_holder == NULL)
	{
		return (NULL);
	}
	
	token = strtok(line, " ");
	while (token != NULL)
	{
		token_holder[i] = token;
		i++;
		if(i >= buffer_size)
		{
			buffer_size +=buffer_size;
			token_holder = realloc(token_holder, buffer_size *sizeof(char*));
			if (token_holder == NULL)
			{
				return (NULL);
			}
		}
		token = strok(NULL, " ");
	}
	
	token_holder[i] = NULL;
	return (token_holder)
}

//execute.c

/**
*execute - function that executes commands
*@args:array of argument strings 
*@Return:
*/

int execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
