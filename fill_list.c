#include "mini.h"

t_name	*tail(t_name *list)
{
	t_name	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}


void	lstadd_back(t_name **lst, t_name *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		tail(*lst)->next = new;
}
t_token	*lstnew(t_token_type type, char *value)
{
	t_token	*linked_lst;

	linked_lst = malloc(sizeof(t_token));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
		
	linked_lst->type = type;
	linked_lst->value = value;
	linked_lst->next = NULL;
	return (linked_lst);
}

t_token *fill_list(char **lst)
{
    t_token_type type;
    char *value;
    int i=0;
    t_token *lst;
    lst=NULL;
    while(lst[i])
    {
		if(ft_strchr(lst[i],'"') || ft_strchr(lst[i],'\''))

        else
        {
            value=ft_strdup(lst[i]);
            if(*value=='|')
                type=TOKEN_PIPE;
            else if(*value=='>')
                type=TOKEN_REDIR_IN;
            else if(*value=='<')
                type=TOKEN_REDIR_OUT;
            else
                type=TOKEN_WORD;

        } 
		lstadd_back(&lst,lstnew(type,value));
		i++;
    }
	return(lst);
}
// if(ft_strchr(lst[i],'|') || ft_strchr(lst[i],'>') || ft_strchr(lst[i],'<'))
