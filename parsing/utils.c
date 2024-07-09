#include "mini.h"

// int ft_strlen(char *str)
// {
//     int i=0;
// 	if(!str)
// 		return 0; 	
//     while(str[i])
//         i++;
//     return i;
// }
// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i] != (const char)c)
// 	{
// 		if (s[i] == '\0')
// 		{
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return ((char *)s + i);
// }
// char	*ft_strdup(const char *s1)
// {
// 	int		i;
// 	char	*str;
// 	char	*s2;

// 	s2 = (char *)s1;
// 	i = 0;
// 	str = malloc(sizeof(char) * ft_strlen(s2) + 1);
// 	if (str == 0)
// 	{
// 		free(str);
// 		return (0);
// 	}
		
// 	while (s2[i])
// 	{
// 		str[i] = s2[i];
// 		i++;
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

char *join(char *s1,char *s2)
{
    int i=0;
    int j=0;
    size_t len1=ft_strlen(s1);
    size_t len2=ft_strlen(s2);
    char *join=malloc(len1+len2+1);
    if(!join)
        return NULL;
    if(!s1 || !s2)
        return NULL;
    while (s1[i])
	{
		join[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		join[j++] = s2[i++];
	}
    join[j]='\0';
    return (join);
}
void get_prompt(char **dst,char *str)
{
	char *tmp;
	tmp=join(*dst,str);
	free(*dst);
	*dst=tmp;
}