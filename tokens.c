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
t_redir	*new_red(int type,char *red)
{
	t_redir	*linked_lst;

	linked_lst = malloc(sizeof(t_redir));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
		
	linked_lst->type = type;
	linked_lst->red=red;
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
    // red_addback(redirection,new_red(int type));
	linked_lst->redirections=redirection;
	linked_lst->next = NULL;
    linked_lst->previous= NULL;
	return (linked_lst);
}
int len(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if((lst->type==2) || (lst->type>=3 && lst->type<=6))
		{
			lst = lst->next;
			if((lst->type>=3 && lst->type<=6))
				lst = lst->next;
		}
		else
			i++;
	}
	return (i);
}
t_lsttoken *fill_token(t_token list)
{
	t_token	*temp;
	t_lsttoken *token=NULL;
	t_lsttoken *token1=NULL;
	t_redir redirections;
	char **args;
	int i=0;
	args=malloc(len(&list)+1*sizeof(char ));
	if(!args)
		return NULL;//free
	temp = &list;
	token=ft_calloc(sizeof(t_lsttoken),1);
	if(!token)
		free(token);
	// if (!list)
	// 	return (NULL);
//should know moore about the struct of arguments tommorow inchallah
	token1 =  token;
	while(temp->next!=NULL)
	{
		//the problem of filling the struct of redirections 
		
		if(temp->type>=2 && temp->type<=6)
		{
			red_addback(&(token->redirections),new_red(temp->type,ft_strdup(temp->next->value)));
			temp = temp->next;
		}
		if(temp->type==2)
		{
			add_back(&token,newnode(temp->type,args,&redirections));
			token = token->next;
		}
		else
		{
			args[i++]=ft_strdup(temp->value);
			
		}
		temp=temp->next;
	
	}
	return token1;
}