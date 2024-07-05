#include "mini.h"
int pipe_frst(char *str)
{
    int i=0;
    while(str[i] && (str[i] == ' ' || str[i] == '\t' ))
        i++;
    if(str[i]=='|')
        return 0;
    //how to access to the last
    i=ft_strlen(str);
    if((str[i-2] != ' ' && str[i-2] != '\t' ) && str[i-1]=='|' && str[i]=='\0' )//this is doesnt work
        return 0;
    return 1;
}
void parsing(char *str)
{
    // char **arr=ft_split(str);
    if(pipe_frst(str)==0)//should know why it doesnt work with some cases and work with case like this "|hell "
        printf("error near `|' \n");
    else 
        printf("good\n");
}