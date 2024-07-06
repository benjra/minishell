#include "mini.h"

size_t	ft_strlcpy(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (n != 0)
	{
		while (src[i] && i < n - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}


char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= len)
		i++;
	if (i >= len)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[len]) && len >= 0)
		len--;
	str = malloc((len - i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)&s1[i], len - i + 2);
	return (str);
}

int pipe_frst(char *tmp)
{
    int i=0;
    char *str;
    str = ft_strtrim(tmp , "\t " );
    i=ft_strlen(str);
    if(str[i-1]=='|' || str[0]=='|')
    {
		return 0;
	}
    return 1;
}

int double_pipe(char *tmp)
{
	int i=0;
    char *str; 
    str = ft_strtrim(tmp , "\t " );
	while(str[i])
	{
		if(str[i]=='|' )
		{
				if(str[i+1]=='|')
					return 0;
				while(str[i+1] && (str[i+1]!=' ' || str[i+1]!='\t'))
				{
					i++;
					if(str[i+1]=='|' )
						return 0;
				}
		}
		i++;
	}
	return 1;
}
void parsing(char *str)
{
    // char **arr=ft_split(str);
    if(pipe_frst(str)==0 || double_pipe(str)==0)
        printf("error near `|' \n");
    else 
        printf("good\n");
}