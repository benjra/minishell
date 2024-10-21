/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:33 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/21 14:00:36 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

int	is_valid_identifier(const char *str)
{
	if (!str || !*str || !(ft_isalpha(*str) || *str == '_'))
		return (0);
	while (*++str)
		if (!(ft_isalnum(*str) || *str == '_'))
			return (0);
	return (1);
}

void	remove_env(t_name **env, const char *var)
{
	t_name	*current;
	t_name	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->name, var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	my_unset(t_name **env, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (cmd[1] && cmd[1][0] == '-')
		{
			ft_putstr_fd("minishell: unset: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			g_var.exit_s = 2;
			return ;
		}
		else if (!is_valid_identifier(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.exit_s = 1;
		}
		else
			remove_env(env, cmd[i]);
		i++;
	}
}
