#include "../parsing/mini.h"

void remove_env(t_name **env, const char *var)
{
    t_name *current = *env;
    t_name *prev = NULL;

    while (current)
    {
        if (ft_strcmp(current->name, var) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *env = current->next;
            free(current->name);
            free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void my_unset(t_name **env, char **cmd)
{
    int i;

    i = 1;
    while (cmd[i])
    {
        if (cmd[1][0] == '-')
        {
            ft_putstr_fd(" unset: -", 2);
            ft_putchar_fd(cmd[i][1], 2);
            ft_putstr_fd(": invalid option\n", 2);
        }
        remove_env(env, cmd[i]);
        i++;
    }
}
