include "mini.h"

char	*ft_strtrim(char  *str)
{
    char **arr;
    int i=0;
    int j=0;
    if(!str)
        return NULL;
    while(*str)
    {
        if(*str!=' ')
            i++;
        str++;
    }
    arr=malloc(i+1);
    if(!arr)
        return(NULL);
    while(*str)
    {
        arr[i][j]=*str;
        while(*str==' ')
            str++;
        str++;
    }
}
int main(int ac,char **av,char **env)
{
    
}
