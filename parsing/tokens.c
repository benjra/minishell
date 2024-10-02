/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:54 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/02 17:10:47 by bbenjrai         ###   ########.fr       */
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
// here we create redirections nodes and add them to redirection list if we find  the type between(3-6)
// here we create a node if we find a pipe (type==2) every pipe represent a node=command

t_lsttoken	*init_token(t_token *list)
{
	t_lsttoken	*token;

	token = ft_calloc(1, sizeof(t_lsttoken));
	if (!token)
		return (NULL);
	token->args = malloc((len(list) + 1) * sizeof(char *));
	if (!token->args)
		return (NULL);
	token->args[len(list)] = NULL;
	token->redirections = NULL;
	return (token);
}

void	handle_redirection(t_token **temp, t_lsttoken *token)
{
	t_redir	*redirections;

	if ((*temp)->next != NULL && (*temp)->type > 2 && (*temp)->type <= 6)
	{
		redirections = new_red((*temp)->type, ft_strdup((*temp)->next->value));
		red_addback(&(token->redirections), redirections);
		(*temp) = (*temp)->next;
	}
}

void	add_new_token_node(t_token **temp, t_lsttoken **token, int *i)
{
	add_back(token, newnode((*temp)->type, (*token)->args));
	*token = (*token)->next;
	(*token)->args = ft_calloc(len((*temp)->next) + 1, sizeof(char *));
	(*token)->args[len((*temp)->next)] = NULL;
	(*token)->redirections = NULL;
	*i = 0;
}

t_lsttoken	*fill_token(t_token *list)
{
	t_token		*temp;
	t_lsttoken	*token[2];
	int			i;

	temp = list;
	i = 0;
	token[0] = init_token(list);
	if (!token[0])
		return (NULL);
	token[1] = token[0];
	while (temp != NULL)
	{
		handle_redirection(&temp, token[0]);
		if (temp->next != NULL && temp->type == 2)
			add_new_token_node(&temp, &token[0], &i);
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
