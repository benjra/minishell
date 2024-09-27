#include "mini.h"
char *ins_quote(char *str)
{
    int i;
    int len;
    char c;
    char *tmp[2];
    char *res;

    i=0;
    len=i;
    res= ft_strdup("");
    while(str[len])
    {
        tmp[0] = res;
        if(str[len]=='"' || str[len]=='\'')
        {
            c=str[len++];
            i=len;
            while(str[len] && str[len]!=c)
                len++;
            tmp[1] = ft_substr(str,i,len-i);
            if (str[len])
            {
                res=ft_strjoin(res,tmp[1]);
                len++;
            }
            else
            {
                res=ft_strjoin(res,tmp[1]);
            }
        }
        else
        {
            i =len;
            while(str[len] && str[len]!='"' && str[len]!='\'')
                len++;
            tmp[1] = ft_substr(str,i,len-i);
            res=ft_strjoin(res,tmp[1]);
        }
        free(tmp[1]);
        free(tmp[0]);
    }
    return res;
}

// void rm_quotes(t_lsttoken *tokens)//func for removing the quotes 
// {
//     t_lsttoken *tmp;
//     int i;
//     tmp=tokens;
//     while (tmp)
//     {
//         i=0;
//         while (tmp->args[i])
//         {
//             if((ft_strchr(tmp->args[i],'\'') ) || (ft_strchr(tmp->args[i],'"') ))
//                 tmp->args[i]=ft_strdup(ins_quote(tmp->args[i]));
//             i++;
//         }
//         tmp=tmp->next;
//     }
// }
