#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

void custom_perror(const char *msg)
{
    perror(msg);
}

size_t _strlen(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return len;
}

int _strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int custom_tokenize(char *input, char *args[], int max_args)
{
    int num_args = 0;
    char *token = strtok(input, " ");

    while (token != NULL && num_args < max_args - 1)
    {
        args[num_args] = token;
        num_args++;
        token = strtok(NULL, " ");
    }
    args[num_args] = NULL;
    return num_args;
}

int isExecutable(const char *path)
{
    if (access(path, X_OK) == 0)
    {
        return 1;
    }
    return 0;
}

int customShell(void)
{
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARGS];
    int num_args;
    pid_t pid;

    while (1)
    {
        int input_size = read(STDIN_FILENO, input, MAX_INPUT_SIZE);

        if (input_size < 0)
        {
            custom_perror("Read error");
            break;
        }

        if (input_size == 0)
        {
            break;
        }

        write(STDOUT_FILENO, "simpleshell > ", _strlen("simpleshell > "));
        input[input_size - 1] = '\0';
        num_args = custom_tokenize(input, args, MAX_ARGS);

        if (num_args > 0)
        {
            if (_strcmp(args[0], "exit") == 0)
            {
                break;
            }

            /*pid_t pid;*/
            if ((pid = fork()) < 0)
            {
                custom_perror("Fork failed");
            }
            else if (pid == 0)
            {
                if (execvp(args[0], args) == -1)
                {
                    custom_perror("Execution error");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }

    return 0;
}

int main(void)
{
    customShell();
    return 0;
}
