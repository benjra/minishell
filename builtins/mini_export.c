/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:14:33 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/08 19:32:24 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	swap_nodes(t_name *a, t_name *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

t_name	*bubble_sort_env(t_name *env)
{
	int		swapped;
	t_name	*ptr1;
	t_name	*lptr;

	if (!env)
		return (NULL);
	lptr = NULL;
	while (1)
	{
		swapped = 0;
		ptr1 = env;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
		if (!swapped)
			break ;
	}
	return (env);
}

void	print_export(t_name *env)
{
	t_name	*current;

	current = bubble_sort_env(env);
	while (current)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(current->name, 1);
		if (current->value != NULL)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}

void	handle_no_cmd(t_name **env)
{
	t_name	*env_copy;

	env_copy = copy_env(*env);
	if (!env_copy)
		return ;
	print_export(env_copy);
	free_env(env_copy);
}

void	my_export(t_name **env, char **cmd)
{
	int	i;

	g_var.exit_s = 0;
	if (cmd[1] == NULL)
	{
		handle_no_cmd(env);
		return ;
	}
	i = 1;
	while (cmd[i])
	{
		process_cmd(env, cmd, i);
		i++;
	}
	sync_env_array(*env);
}
