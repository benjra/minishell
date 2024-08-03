// two case in ambiguis errors when 
// $var doesnt exist ==null 
//or when we export a variable like $var="ac ch" found space inside 


//should handle all syntax errors 
#include "mini.h"
int pipes_err(t_token *list)
{
    t_token *tmp;
    tmp=list;
    if(list->type==2)
        return 1;
    if(tails(list)->type==2)
        return (2);
    while (tmp!=NULL)
    {
        if(tmp->type==2 && tmp->next->type==2)
            return (1);
        tmp=tmp->next;
    }
    return (0);
}
void printf_err(t_token *list)
{
    if(pipes_err(list)==1)
        printf("error near `|' \n");
    if(pipes_err(list)==2)
        printf("syntax error! \n");
}