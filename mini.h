#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
typedef struct s_name
{
    char *name;
    char *value;
    struct s_name *next;
}t_name;

typedef struct list1
{
    char *str;
    struct list1 *next;
} t_list1;

char    **ft_split(char *str);
int ft_strlen(char *str);
void prompt();
