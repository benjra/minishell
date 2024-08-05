#include "mini.h"
char *ft_env(t_name *env,char *var)
{
    t_name *temp;
    temp=env;
    char *replace;
    while(temp)
    {
        if(ft_strncmp(temp->name,var, ft_strlen(var)) == 0)
        {
            replace=ft_strdup(temp->value);
            return (replace);
        }
    temp=temp->next;    
    }
    return (NULL);
}