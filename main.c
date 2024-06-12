//#include "mini.h"
#include <stdlib.h>
#include <stdio.h>
char	**ft_strtrim(char  *str)
{
    char **arr;
    int i=0;
    int j=0;
    // if(!str)
    //     return NULL;
    while(*str)
    {
        if(*str!=' ')
            i++;
        str++;
    }
    arr=malloc(i+1);
    i=0;
    if(!arr)
        return(NULL);
    while(*str)
    {
        arr[i][j]=*str;
        if(*str==' ')
        {
            j++;
            i=0;
        } 
        while(*str==' ')
        {
            str++;
        }
        str++;
    }
    return (arr);
}
// char	*tstring(char **av, int len)
// {
// 	int		i;
// 	int		j;
// 	char	*str;
// 	int		k;

// 	i = 1;
// 	j = 0;
// 	k = 0;
// 	str = malloc((len + 1) * sizeof(char *));
// 	if (!str)
// 		freenull(str);
// 	while (av[i])
// 	{
// 		j = 0;
// 		while (av[i][j])
// 		{
// 			str[k++] = av[i][j++];
// 			if (av[i][j] == '\0')
// 				str[k++] = ' ';
// 		}
// 		i++;
// 	}
// 	str[k - 1] = '\0';
// 	return (str);
// }
int main(int ac,char **av,char **env)
{
    // char *str=tstring(av,)
    char **arr=ft_strtrim(av[1]);
    int i=0;
    while(arr[i])
        printf("%s\n",arr[i++]);
}
