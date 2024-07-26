#include "mini.h"

 t_redir	*last_red(t_redir *list)
{
	t_redir	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	red_addback(t_redir **lst, t_redir *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
    {
        last_red(*lst)->next = new;
        new->previous=last_red(*lst);
    }
}
t_redir	*new_red(int type)
{
	t_redir	*linked_lst;

	linked_lst = malloc(sizeof(t_redir));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
		
	linked_lst->type = type;
	linked_lst->next = NULL;
    linked_lst->previous= NULL;
	return (linked_lst);
}
///llstoken--------------------
t_lsttoken	*last(t_lsttoken *list)
{
	t_lsttoken	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	add_back(t_lsttoken **lst, t_lsttoken *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
    {
        last(*lst)->next = new;
        new->previous=last(*lst);
    }
}

t_lsttoken	*newnode(int type, char **args,t_redir *redirection)
{
	t_lsttoken	*linked_lst;

	linked_lst = malloc(sizeof(t_lsttoken));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
		
	linked_lst->type = type;
	linked_lst->args = args;
    red_addback(redirection,new_red(int type));
	linked_lst->next = NULL;
    linked_lst->previous= NULL;
	return (linked_lst);
}

t_lsttoken *fill_token(t_token list)
{
	t_token	*temp;
	t_lsttoken *token=NULL;
	int type=1;
	char **args;
	args=malloc
	temp = list;
	if (!list)
		return (NULL);
//should know moore about the struct of arguments tommorow inchallah
	while(temp->next!=NULL)
	{
		//the problem of filling the struct of redirections 
		if(ft_strchr(list->value,'|'))
			add_back(&token,newnode());
	}
}