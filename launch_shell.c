#include "shell.h"

/**
*launch_shell - launches the shell
*@args: array of argument strings
*Return: always success
*/

int launch_shell(char **args)
{
    pid_t pid, wpid;
    int status;
	path(args);
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
