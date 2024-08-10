#include "mini.h"
char *ins_quote(char *str)
{
    char *ins_quote=NULL;
    int i;
    int len;
    char c;
    char *res;

    i=0;
    len=i;
    while(str[len])
    {
        if(str[len]=='"' || str[len]=='\'')
        {
            c=str[len++];
            i=len;
            while(str[len] && str[len]!=c)
            {
                len++;
            }
            len++;
        }
        if(str[i])
            len++;
    }
    res=ft_substr(str,i,len);
}
void rm_quotes(t_lsttoken *tokens)
{
    t_lsttoken *tmp;
    int i;
    tmp=tokens;
    while (tmp)
    {
        i=0;
        while (tmp->args[i])
        {
            if(ft_strncmp(tmp->args[i],"'",1)==0 || ft_strncmp(tmp->args[i],"'",1)==0)
                tmp->args[i]=ft_strdup(ins_quote(tmp->args[i]));
            i++;
        }
    }
}