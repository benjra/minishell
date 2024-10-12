#include "../parsing/mini.h"

void	validate_exit(char **argv, int is_valid, int argc)
{
    if (argc == 1)
    {
        gl_ex = 1;
        ft_putstr_fd("exit\n", 1);
        exit(0);
    }
    else if (!is_valid)
    {
        ft_putstr_fd("exit\nexit: ", 2);
        ft_putstr_fd(argv[1], 2);
        ft_putstr_fd(": numeric argument required\n", 2);
        exit(255);
    }
    else if (argc > 2)
    {
        ft_putstr_fd("exit\nexit: too many arguments\n", 2);
        return ;
    }
    else if (argv[1])
    {
        gl_ex = 1;
        exit(ft_atoi(argv[1]) % 256);
    }
}

int	my_exit(char **argv)
{
    int	is_valid;
    int	i;
    int	j;

    is_valid = 1;
    i = 1;
    j = 0;
    if (argv[i] && (argv[i][j] == '-' || argv[i][j] == '+'))
        j++;
    if (argv[i] && !argv[i][j])
        is_valid = 0;
    while (argv[i] && argv[i][j] && is_valid)
    {
        if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
            is_valid = 0;
        j++;
    }
    while (argv[i])
        i++;
    validate_exit(argv, is_valid, i);
    return (0);
}
