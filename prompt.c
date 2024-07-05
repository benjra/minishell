#include "mini.h"

// char *gethost()
char *prompt()
{
    char *ptr;
    ptr= ft_strdup(BGreen);
    get_prompt(&ptr,">>>");
    get_prompt(&ptr,BWhite);
    return (ptr);
}