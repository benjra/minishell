#include "../parsing/mini.h"

int	ft_isspace(int c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

char	*trim_spaces(char *str)
{
    char	*end;

    while (ft_isspace((unsigned char)*str))
        str++;
    if (*str == 0)
        return (str);
    end = str + ft_strlen(str) - 1;
    while (end > str && ft_isspace((unsigned char)*end))
        end--;
    *(end + 1) = '\0';
    return (str);
}

void	error(const char *s, int ss)
{
    perror(s);
    exit(ss);
}

char	*skipp(char *str)
{
    return (ft_strchr(str, '=') + 1);
}

void	ft_free(char **av)
{
    int	i;

    i = 0;
    while (av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}
