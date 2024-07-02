#include "mini.h"

int ft_strlen(char *str)
{
    int i=0;
    while(str[i])
        i++;
    return i;
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (const char)c)
	{
		if (s[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((char *)s + i);
}
char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str;
	char	*s2;

	s2 = (char *)s1;
	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s2) + 1);
	if (str == 0)
		return (0);
	while (s2[i])
	{
		str[i] = s2[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}