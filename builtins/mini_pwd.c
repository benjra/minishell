/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:22 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/21 14:06:16 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

static void	handle_invalid_option(char **av)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(av[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	g_var.exit_s = 2;
}

static void	print_cwd(char *cwd)
{
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	g_var.exit_s = 0;
}

static void	print_pwd_env(t_name *env)
{
	t_name	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD", 3) == 0)
		{
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
			g_var.exit_s = 0;
			return ;
		}
		tmp = tmp->next;
	}
	ft_putstr_fd("minishell: pwd: ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	g_var.exit_s = errno;
}

void	my_pwd(t_name *env, char **av)
{
	char	cwd[PATH_MAX];

	if (av[1] && av[1][0] == '-')
	{
		handle_invalid_option(av);
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		print_cwd(cwd);
		return ;
	}
	print_pwd_env(env);
}
