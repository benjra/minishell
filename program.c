/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/08 21:32:07 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	program_name(char **en)
{
	// char	*prom;
	t_name	*env;
	char	*cmd;

	env = fill_env(en);
	while (1)
	{
		// prom = ft_strdup(BGreen);
		// prom = join(prom, "minishell$ ");
		// prom = join(prom, RESET_COLOR);
		// if (!prom)
			// exit(1);
		cmd = readline("\033[1;32mminishell$ \e[m"); // u should know how to work with readline
		if (!cmd)
			break ;
		if (ft_strncmp(cmd, "", -1))
		{
			add_history(cmd);
			parsing(cmd, env);
		}
		free(cmd);
	}
	free_env(env);
	rl_clear_history();
	// free_env() //should add this func
}
