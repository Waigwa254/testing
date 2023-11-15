#include "shell.h"

char *custom_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        ++s;
    }

    return NULL;
}

size_t custom_strcspn(const char *s, const char *reject)
{
    size_t count = 0;

    while (*s)
    {
        if (custom_strchr(reject, *s))
            break;
        ++s;
        ++count;
    }

    return count;
}

