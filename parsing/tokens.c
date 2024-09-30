/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:54 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/30 11:59:07 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

// this function fillling the last list from a normal list
t_lsttoken	*fill_token(t_token *list)
{
	t_token *temp;
	t_lsttoken *token[2];
	t_redir *redirections;
	int i;

	token[0] = NULL;
	token[1] = NULL;
	i = 0;
	temp = list;
	token[0] = ft_calloc(1, sizeof(t_lsttoken));
	if (!token[0])
		return (NULL);
	token[0]->args = malloc((len(temp) + 1) * sizeof(char *));
	token[0]->args[len(temp)] = NULL;
	token[0]->redirections = NULL;
	token[1] = token[0];
	while (temp != NULL)
	{
		if (temp->next != NULL && temp->type > 2 && temp->type <= 6)// here we create redirections nodes and add them to redirection list if we find  the type between(3-6)
		{
			redirections = new_red(temp->type, ft_strdup(temp->next->value));
			red_addback(&(token[0]->redirections), redirections);
			temp = temp->next;
		}
		else if (temp->next != NULL && temp->type == 2)// here we create a node if we find a pipe (type==2) every pipe represent a node=command
		{
			add_back(&token[1], newnode(temp->type, token[0]->args));
			token[0] = token[0]->next;
			token[0]->args = ft_calloc(len(temp->next) + 1, sizeof(char *));
			token[0]->args[len(temp->next)] = NULL;
			token[0]->redirections = NULL;
			i = 0;
		}
		else
		{
			token[0]->args[i++] = ft_strdup(temp->value);
			token[0]->args[i] = NULL;
 		}
		if (temp != NULL)
			temp = temp->next;
	}
	return (token[1]);
}
