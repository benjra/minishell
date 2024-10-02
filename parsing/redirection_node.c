/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:56:54 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/30 11:57:05 by bbenjrai         ###   ########.fr       */
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
	t_redir *linked_lst;

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