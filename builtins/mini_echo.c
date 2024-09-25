#include "../parsing/mini.h"

int	is_n_option(char *arg)
{
    int	i;
    if (arg[0] != '-' || arg[1] == '\0')
        return (0);
    i = 1;
    while (arg[i] != '\0')
    {
        if (arg[i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int	my_echo(char **av)
{
    int	newline;
    int	arg_start;
    int	i;

    newline = 1;
    arg_start = 1;
    while (av[arg_start] && is_n_option(av[arg_start]))
    {
        newline = 0;
        arg_start++;
    }
    i = arg_start;
    while (av[i])
    {
        ft_putstr_fd(av[i], 1);
        if (av[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);
    return (0);
}
