#ifndef SHELL_H
#define SHELL_H

/*--HEADER FILES--*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TOK_BUFSIZE 1024


/*--FUNCTION PROTOTYPES--*/
void prompt(void);
char *read_line(void);
char **parser(char *line);
int execute(char **args);
int get_builtin(char *cmd);
int exit_shell(char **args);
int cd_shell(char **args);
int get_help(char **args);
int path (char **args);

#endif
