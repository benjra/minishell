//#include "mini.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arrlen(char **av)
{
    int i;
    int j;
    int len;
    len=0;
    i=0;
    while(av[i])
    {
        j=0;
        while(av[i][j]==' ')
            j++;
        while(av[i][j])
        {
            if(av[i][j]!=' ')
                len++;
            j++;
        }
        i++;
    }
    return (len);
}

char ** cmdtrim(char *str)
{
    int start=0;
    int end=0;
    int i=0;
    char string=malloc(sizeof(char *))
 
while (*str)
	{
		while (*str && *str == ' ')
			str++;
		if (*str)
		{
			string[index_string] = alloc((char *)s, c);
			if (!string[index_string])
				return (free_split(string, index_string));
			index_string++;
		}
		while (*s && *s != c)
			s++;
	}
}
// char	**ft_strtrim(char  **str)
// {
//     char **arr;
//     int i=0;
//     int j=0;
    
//     while(*str)
//     {
//         if(*str!=' ')
//             i++;
//         str++;
//     }
//     arr=malloc(i+1);
//     i=0;
//     if(!arr)
//         return(NULL);
//     while(*str)
//     {
//         arr[i][j]=*str;
//         if(*str==' ')
//         {
//             j++;
//             i=0;
//         } 
//         while(*str==' ')
//         {
//             str++;
//         }
//         str++;
//     }
//     return (arr);
// }

char	*tstring(char **av, int len)
{
	int		i;
	int		j;
	char	*str;
	int		k;

	i = 1;
	j = 0;
	k = 0;
	str = malloc((len + 1) * sizeof(char *));
	if (!str)
		{
            free(str);
            return NULL;
        }
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			str[k++] = av[i][j++];
			if (av[i][j] == '\0')
				str[k++] = ' ';
		}
		i++;
	}
	str[k - 1] = '\0';
	return (str);
}

int main(int ac,char **av,char **env)
{
    char *str=tstring(av,arrlen(av));
    int i=0;
    // while(arr[i])
        printf("%s\n",str);
}
