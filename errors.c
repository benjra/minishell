// two case in ambiguis errors when 
// $var doesnt exist ==null 
//or when we export a variable like $var="ac ch" found space inside 


//should handle all syntax errors 
#include "mini.h"
int double_symb(t_token *list)
{
    t_token *tmp;
    tmp=list;
    int typo;
    int nextp;
    while(tmp!=NULL)
    {
        if(tmp->next!=NULL)
        {
            typo=tmp->type;
            nextp=tmp->next->type;
            if(typo==3 || typo==4 || typo==5 || typo==6) // this case "ls <| ls" it return 0 in this case why ?
            {
                if(nextp==2 || nextp==3 || nextp==4 || nextp==5 || nextp==6 )
                    return 1;
            }
        }        
        tmp=tmp->next;
    }
    return 0;
}
int pipes_err(t_token *list)
{
    t_token *tmp;
    tmp=list;
    if(list->type==2)
        return 1;
    if(tails(list)->type==2 ||  tails(list)->type==3 || tails(list)->type==4 || tails(list)->type==5 || tails(list)->type==6)
        return (2);
    while (tmp!=NULL)
    {
        if(tmp->type==2 && (!tmp->next || tmp->next->type==2))
            return (1);
        tmp=tmp->next;
    }
    return (0);
}
int handle_quotes(t_token *list)
{
    t_token *tmp;
    int i;
    tmp=list;
    while (tmp)
    {
        if(ft_strchr(tmp->value,'\'') || ft_strchr(tmp->value,'"'))
        {   
            char *first_quote;
            if(ft_strchr(tmp->value,'\''))
            {
                first_quote=ft_strchr(tmp->value,'"');
                first_quote++;
                    i=0;
                while(first_quote[i])
                {
                    if((first_quote[i])=='\'')
                        return (0);
                    i++;
                }
            }
            else if(ft_strchr(tmp->value,'"'))
            {
                first_quote=ft_strchr(tmp->value,'"');
                first_quote++;
                    i=0;
               while(first_quote[i])
                {
                    if((first_quote[i])=='"')
                        return (0);
                    i++;
                }
            }
        }
        tmp=tmp->next;
    }
    return (1);
    
}
void printf_err(t_token *list)
{
    printf("%d\n", double_symb(list));
    if(pipes_err(list)==1)
        printf("error near `|' \n");
    if(pipes_err(list)==2 || double_symb(list)==1 || handle_quotes(list))
        printf("syntax error! \n");
}