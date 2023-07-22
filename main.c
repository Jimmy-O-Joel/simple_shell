#include "shell.h"

/**
*main - entry point of our program
*@ac: arguments
*@av: argument vector
*@env: environment
*Return: Always 0
*/


int main(__attribute__((unused)) int ac,
		__attribute__((unused)) char **av, char **env)
{
	prompt(env);
	return (0);

}
