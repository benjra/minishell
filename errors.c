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
        if(tmp->next!=NULL){
            typo=tmp->type;
            nextp=tmp->next->type;
            if(typo==3 || typo==4 || typo==5 || typo==6)
            {
                if(nextp==3 || nextp==4 || nextp==5 || nextp==6)
                    return 1;
            }
            tmp=tmp->next;
        }
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
    if(pipes_err(list)==2 || double_symb(list)==1)
        printf("syntax error! \n");
}