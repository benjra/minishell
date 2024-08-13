/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:54 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/13 10:12:51 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_redir	*last_red(t_redir *list)
{
	t_redir	*temp;

	if (!list)
		return (NULL);
	temp = list;
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
		new->next = NULL;
		new->previous = last_red(*lst);
	}
}

t_redir	*new_red(int type, char *red)
{
	t_redir	*linked_lst;

	linked_lst = malloc(sizeof(t_redir));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
	linked_lst->type = type;
	linked_lst->red = red;
	linked_lst->next = NULL;
	linked_lst->previous = NULL;
	return (linked_lst);
}

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
	{
		*lst = new;
	}
	else
	{
		last(*lst)->next = new;
		new->next = NULL;
		new->previous = last(*lst);
	}
}

t_lsttoken	*newnode(int type, char **args)
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
	linked_lst->next = NULL;
	linked_lst->previous = NULL;
	return (linked_lst);
}

int	len(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (lst->type == 2)
			break ;
		if ((lst->type >= 3 && lst->type <= 6))
		{
			lst = lst->next;
		}
		else
			i++;
		lst = lst->next;
	}
	return (i);
}

t_lsttoken	*fill_token(t_token *list)//this function fillling the last list from a normal list
{
	t_token		*temp;
	t_lsttoken	*token;
	t_lsttoken	*token1;
	t_redir		*redirections;
	int			i;

	token = NULL;
	token1 = NULL;
	i = 0;
	temp = list;
	token = ft_calloc(1, sizeof(t_lsttoken));
	if (!token)
		return (NULL);
	token->args = malloc((len(temp) + 1)* sizeof(char *));
	token->args[len(temp)] = NULL;
	token->redirections = NULL;
	token1 = token;
	while (temp != NULL)
	{
		if (temp->next != NULL && temp->type > 2 && temp->type <= 6)//here we create redirections nodes and add them to redirection list if we find  the type between(3-6)
		{
			redirections = new_red(temp->type, ft_strdup(temp->next->value));
			red_addback(&(token->redirections), redirections);
			temp = temp->next;
		}
		else if (temp->next != NULL && temp->type == 2) //here we create a node if we find a pipe (type==2) every pipe represent a node=command
		{
			add_back(&token1, newnode(temp->type, token->args));
			token = token->next;
			token->args = ft_calloc(len(temp->next) + 1, sizeof(char *));
			token->args[len(temp->next)] = NULL;
			token->redirections = NULL;
			i = 0;
		}
		else
			token->args[i++] = ft_strdup(temp->value);
		if (temp != NULL)
			temp = temp->next;
	}
	return (token1);
}
