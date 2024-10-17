#include "../parsing/mini.h"

void my_pwd(t_name *env, char **av)
{
    char    cwd[PATH_MAX];
    t_name *tmp;

    if (av[1] && av[1][0] == '-')
    {
        ft_putstr_fd("minishell: pwd: ", 2);
        ft_putstr_fd(av[1], 2);
        ft_putstr_fd(": invalid option\n", 2);
		g_var.exit_s = 2;
        return ;
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_putstr_fd(cwd, 1);
        ft_putstr_fd("\n", 1);
        g_var.exit_s = 0;
        return ;
    }
    else
    {
        tmp = env;
        while(tmp)
        {
            if(ft_strncmp(tmp->name,"PWD",3) == 0)
            {
                ft_putstr_fd(tmp->value, 1);
                ft_putstr_fd("\n", 1);
                g_var.exit_s = 0;
                return ;
            }
            tmp = tmp->next;
        }
    }
    ft_putstr_fd("minishell: pwd: ", 2);
    ft_putstr_fd(strerror(errno), 2);
    ft_putstr_fd("\n", 2);
    g_var.exit_s = errno;
}
