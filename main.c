#include "mini.h"
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
int pipe_frst(char *str)
{
    int i=0;
    while(str[i] && (str[i] == ' ' || str[i] == '\t' ))
        i++;
    if(str[i]=='|')
        return 0;
    //how to access to the last
    i=ft_strlen(str);
    if((str[i-2] != ' ' && str[i-2] != '\t' ) && str[i-1]=='|' && str[i]=='\0' )
        return 0;
    return 1;
}
int main(int ac,char **av)//,char **env)
{
	(void)ac;
    char *str=tstring(av,arrlen(av));
    
	char **arr=ft_split(str);
    if(pipe_frst(str)==0)//should know why it doesnt work
        printf("zsh: parse error near `|'");
    free(str);
    printf("%s",arr[0]);
    // free(arr);
}
//first should if u find a pipe in the first or last throw an error o|| if u find  || two pipes throw an error
//should firstly make a just split by space and then fill the node based at the pipes or redirections or quotations
//make a list for the envirement with two members name and value
