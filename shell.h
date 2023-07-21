#ifndef SHELL_H
#define SHELL_H

/*--HEADER FILES--*/


#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define TOK_BUFSIZE 1024
#define BUFSIZE 1024

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
int execute(char **args, char **_environ);
int launch_shell(char **args);
int get_help(char **args);
int path(char **args);
void prompt(char **_environ);
int exit_shell(char **args, char **_environ);
int _env(char **args, char **_environ);
void free_tokens(char **tokens);

void cd_dotdot(char **_environ);
void cd_to(const char *dir, char **_environ);
void cd_previous(char **_environ);
void cd_home(char **_environ);
int cd_shell(char **args, char **_environ);
int cd_custom(char *dir, char **_environ);

int cmp_env_name(const char *nenv, const char *name);
char *_getenv(const char *name, char **_environ);
char *copy_info(char *name, char *value);
int set_env(const char *name, const char *value, char **_environ);
int _setenv(char **args, char **_environ);
int _unsetenv(char **args, char **_environ);


char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char *str, const char *delim);
void rev_string(char *s);

void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif
