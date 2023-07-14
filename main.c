//main.c
#include "shell.h"

/* Built-in command names and corresponding functions */

const char *builtin_str[] = {"cd","exit\n","help\n"};

int (*builtin_func[]) (char **) = {
    &cd_shell,
    &exit_shell
};

/**
*main - entry point of our program
*
*Return: Always 0
*/


int main(int argc, char **argv)
{
	prompt();
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

//read_line.c

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
*Return: pointer to an array
*/
char **parser(char *line)
{

	int buf_size = TOK_BUFSIZE;
	int i = 0;
	char **token_holder;
	char *token;
	
	token_holder = (char**)malloc(buf_size * sizeof(char *));
	if (token_holder == NULL)
	{
		return (NULL);
	}
	
	token = strtok(line, " ");
	while (token != NULL)
	{
		token_holder[i] = token;
		i++;
		if(i >= buf_size)
		{
			buf_size +=buf_size;
			token_holder = realloc(token_holder, buf_size *sizeof(char*));
			if (token_holder == NULL)
			{
				return (NULL);
			}
		}
		token = strtok(NULL, " ");
	}
	
	token_holder[i] = NULL;
	return (token_holder);
}



/**
 * cd_shell - change to another directory
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int cd_shell(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
 
int exit_shell(char **args)
{
  return 0;
}

/**
*launch_shell - launches the shell
*@args: array of argument strings
*Return: always success
*/

int launch_shell(char **args)
{
    pid_t pid, wpid;
    int status;
    
    pid = fork();
    
    if (pid == 0)
    {
        /* Child process */
        if (execv(args[0], args) == -1)
        {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Error forking */
        perror("lsh");
    }
    else
    {
        /* Parent process */
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    
    return 1;
}
		



//execute.c

/**
*execute - function that executes commands
*@args:array of argument strings 
*Return:
*/

int execute(char **args)
{

	int i;
	int equal;
	
    if (args[0] == NULL)
    {
        return 1;  /* Empty command */
    }
    
    for (i = 0; i < sizeof(builtin_str) / sizeof(char *); i++)
    {
        if (strcmp(builtin_str[i], args[0]) == 0)
        {
            return (*builtin_func[i])(args);
        }

    }
    
    return launch_shell(args);
}

//finding PATH
/**
*path - searches in $PATH for an executable command
*@args: parsed input
*Return: 0 on success, 1 on failure
*/

int path (char **args)
{

    /* REtriving path directory using getenv */
	char *path;
	char *token;
	char command_path [100];

	path = getenv("PATH");

	/* tokenize the path variale to otain individual directory paths */

	token = strtok(path, ":");
	while ( token != NULL)
	{
		/* construct the full path of the command using the strcpy, strcat functions */
		strcpy(command_path , token);
		strcat(command_path, "/");
		strcat(command_path, args[0]);

		/* check if the command exists and is executable */

			if (access(command_path, X_OK) == 0)
			{
				/* execute the command using execvp */
				args[0] = command_path;
				if (execvp(args[0], args) == -1)
				{
					perror("execvp")
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
