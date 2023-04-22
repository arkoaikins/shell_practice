#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - Executes the command "ls -l /tmp" in 5 child processes.
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t child_pid;
    int i = 0, status;
    char *argv[] = {"ls", "-l", "/tmp", NULL};

    while (i < 5)
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            printf("Error: Fork failed.\n");
            exit(1);
        }
        else if (child_pid == 0)
        {
            if (execve("/bin/ls", argv, NULL) == -1)
            {
                printf("Error: execve failed.\n");
                exit(1);
            }
        }
        else
        {
            wait(&status);
            i++;
        }
    }

    return (0);
}
