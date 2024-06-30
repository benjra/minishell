#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
typedef struct list1
{
    char *str;
    struct list1 *next;
} t_list1;

char    **ft_split(char *str);
int ft_strlen(char *str);
