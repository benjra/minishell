#include "../parsing/mini.h"

void	print_env(t_name *env)
{
    t_name *current;

    current = env;
	while (current)
	{
		if (current->value)
        {
            ft_putstr_fd(current->name, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(current->value, 1);
            ft_putstr_fd("\n", 1);
        }
		current = current->next;
	}
}

int my_env(t_name *env, char **cmd)
{
    if (!env)
        ft_putstr_fd("env is null\n", 2);
    else if (cmd[1] == NULL)
        print_env(env);
    else if (cmd[1][0] == '-')
    {
        ft_putstr_fd("env: invalid option -- '", 2);
        ft_putstr_fd(cmd[1], 2);
        ft_putstr_fd("'\n", 2);
        return (125);
    }
    else
    {
        ft_putstr_fd("env: ‘", 2);
        ft_putstr_fd(cmd[1], 2);
        ft_putstr_fd("’: No such file or directory\n", 2);
        return (127);
    }
    return (0);
}
