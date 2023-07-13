#ifndef SHELL_H
#define SHELL_H

/--HEADER FILES--/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/--FUNCTION PROTOTYPES--/
void prompt(void);
char *read_line(void);
char **parser(char *line);
int execute(char **args);

#endif
