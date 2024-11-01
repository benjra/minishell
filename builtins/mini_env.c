/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:14:18 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:14:20 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	print_env(t_name *env)
{
	t_name	*current;

	current = env;
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->name, g_var.out_fd);
			ft_putstr_fd("=", g_var.out_fd);
			ft_putstr_fd(current->value, g_var.out_fd);
			ft_putstr_fd("\n", g_var.out_fd);
		}
		current = current->next;
	}
}

void	my_env(t_name *env, char **cmd)
{
	g_var.exit_s = 0;
	if (!env)
		ft_putstr_fd("env is null\n", 2);
	else if (cmd[1] == NULL)
		print_env(env);
	else if (cmd[1][0] == '-')
	{
		ft_putstr_fd("env: invalid option -- '", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("'\n", 2);
		g_var.exit_s = 125;
	}
	else
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		g_var.exit_s = 127;
	}
}

t_name	*find_env_var(t_name *env, const char *var)
{
	while (env)
	{
		if (ft_strcmp(env->name, var) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
