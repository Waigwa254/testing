#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>

void custom_perror(const char *msg);
size_t _strlen(const char *str);
int _strcmp(const char *s1, const char *s2);
int custom_tokenize(char *input, char *args[], int max_args);
int isExecutable(const char *path);
int customShell(void);

#endif

