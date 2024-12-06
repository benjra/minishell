/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:18:06 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/06 02:18:08 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

static void	init_copy_env(t_name **new_env, t_name **last_node)
{
	*new_env = NULL;
	*last_node = NULL;
}

static t_name	*process_env_node(t_name *current, t_name **last_node)
{
	t_name	*new_node;
	int		has_value;

	if (!current || !current->name)
		return (NULL);
	has_value = 0;
	if (current->value != NULL)
		has_value = 1;
	new_node = create_new_node(current->name, current->value, has_value);
	if (!new_node)
		return (NULL);
	if (*last_node)
		(*last_node)->next = new_node;
	*last_node = new_node;
	return (new_node);
}

t_name	*copy_env(t_name *env)
{
	t_name	*new_env;
	t_name	*current;
	t_name	*last_node;
	t_name	*new_node;

	if (!env)
		return (NULL);
	init_copy_env(&new_env, &last_node);
	current = env;
	while (current)
	{
		new_node = process_env_node(current, &last_node);
		if (!new_node)
		{
			free_env(new_env);
			return (NULL);
		}
		if (!new_env)
			new_env = new_node;
		current = current->next;
	}
	return (new_env);
}
