/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:25:19 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/26 15:25:46 by bbenjrai         ###   ########.fr       */
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
