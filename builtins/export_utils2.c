/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:13:38 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:13:39 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

t_name	*create_new_node(const char *var, const char *value, int had_equals)
{
	t_name	*new_node;

	new_node = (t_name *)malloc(sizeof(t_name));
	if (!new_node)
	{
		perror("malloc");
		return (NULL);
	}
	new_node->name = ft_strdup(var);
	if (had_equals == 1)
		new_node->value = set_node_value(value);
	else
		new_node->value = NULL;
	if (!new_node->name || (had_equals && !new_node->value))
	{
		free_node_contents(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

char	*set_node_value(const char *value)
{
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

void	free_node_contents(t_name *node)
{
	if (!node)
		return ;
	free(node->name);
	free(node->value);
	free(node);
}

void	update_existing_node(t_name *current, const char *value, int had_equals)
{
	if (had_equals == 1)
	{
		free(current->value);
		current->value = set_node_value(value);
		if (!current->value)
			perror("malloc");
	}
}

void	sync_env_array(t_name *env)
{
	char	**new_env;

	new_env = env_to_array(env);
	if (!new_env)
		return ;
	free_env_array(g_var.envp);
	g_var.envp = new_env;
}
