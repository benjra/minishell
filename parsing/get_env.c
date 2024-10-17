/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:30 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/15 18:00:32 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_name	*lstnew(char *name, char *value)
{
	t_name	*linked_lst;

	linked_lst = malloc(sizeof(t_name));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
	linked_lst->name = ft_strdup(name);
	linked_lst->value = ft_strdup(value);
	linked_lst->next = NULL;
	return (linked_lst);
}

// this func fill alist from the double pointer **env and return the list
t_name	*fill_env(char **env)
{
	char	*name;
	char	*value;
	char	*en;
	int		i;
	t_name	*lst;

	i = 0;
	if (!env)
		return  ft_calloc(1,sizeof(t_name));
	else
		lst = NULL;
	while (env && env[i])
	{
		en = ft_strdup(env[i]);
		value = ft_strchr(en, '=');
		*value = 0;
		value++;
		name = en;
		lstadd_back(&lst, lstnew(name, value));
		i++;
		free(en);
	}
	return (lst);
}
