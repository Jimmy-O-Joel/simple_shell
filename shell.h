#ifndef SHELL_H
#define SHELL_H

/*--HEADER FILES--*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOK_BUFSIZE 1024

/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} sh_data;

/**
 * struct builtin_s - Builtin struct for command argument.
 * @name: The name of the command builtin
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **args);
} builtin_t;



/*--FUNCTION PROTOTYPES--*/
/*void prompt(void);*/
char *read_line(void);
char **parser(char *line);
int execute(char **args);

int get_help(char **args);
int path(char **args);
int env_shell(char **args);

/*getline */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
static ssize_t read_characters(char **lineptr, size_t *n, FILE *stream);
static void resize_buffer(char **lineptr, size_t *n);

/* ----Refactored prototypes------- */
void prompt(void);
int exit_shell(char **args);
int cd_shell(char **args);

/* execute2 */
int exec_line(char **args);

/* get_builtin */
int (*get_builtin(char *cmd))(char **args);

#endif
