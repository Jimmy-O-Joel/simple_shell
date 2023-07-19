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
int launch_shell(char **args);
int get_help(char **args);
int path(char **args);
int env_shell(char **args);

/* ----Refactored prototypes------- */
void prompt(void);
int exit_shell(char **args);
int cd_shell(char **args);

/* execute2 */
int exec_line(char **args);

/* get_builtin */
int (*get_builtin(char *cmd))(char **args);

#endif
