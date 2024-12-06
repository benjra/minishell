/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:18:14 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/06 02:18:16 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

t_name	*create_and_init_node(const char *var, const char *value,
		int had_equals)
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

void	update_or_add_env_part1(t_name **env, const char *var, t_name **prev,
		t_name **current)
{
	*current = *env;
	*prev = NULL;
	while (*current)
	{
		if (ft_strcmp((*current)->name, var) == 0)
			return ;
		*prev = *current;
		*current = (*current)->next;
	}
}

void	update_or_add_env(t_name **env, const char *var, const char *value,
		int had_equals)
{
	t_name	*current;
	t_name	*prev;
	t_name	*new_node;

	update_or_add_env_part1(env, var, &prev, &current);
	if (current)
	{
		update_existing_node(current, value, had_equals);
		return ;
	}
	new_node = create_and_init_node(var, value, had_equals);
	if (!new_node)
		return ;
	if (prev)
		prev->next = new_node;
	else
		*env = new_node;
}

void	process_cmd(t_name **env, char **cmd, int i)
{
	char	*eq_pos;
	char	*var;
	char	*value;
	int		had_equals;

	eq_pos = ft_strchr(cmd[i], '=');
	var = cmd[i];
	value = NULL;
	had_equals = 0;
	if (eq_pos)
	{
		*eq_pos = '\0';
		value = eq_pos + 1;
		had_equals = 1;
	}
	if (!is_valid_identifier(var))
	{
		handle_invalid_identifier(cmd[i]);
		if (eq_pos)
			*eq_pos = '=';
		return ;
	}
	update_or_add_env(env, var, value, had_equals);
	if (eq_pos)
		*eq_pos = '=';
}

void	handle_invalid_identifier(const char *cmd)
{
	char	*tmp;

	ft_putstr_fd("minishell: export: `", 2);
	tmp = (char *)cmd;
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_var.exit_s = 1;
}
