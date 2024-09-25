/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/15 14:18:21 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	program_name(char **en)//this function is for displaying the promt and read from the readline 
{
	// char	*prom;
	t_name	*env;
	char	*cmd;

	env = fill_env(en);
	env->ev = en;
	while (1)
	{
		// prom = ft_strdup(BGreen);
		// prom = join(prom, "minishell$ ");
		// prom = join(prom, RESET_COLOR);
		// if (!prom)
			// exit(1);
		cmd = readline("\033[1;32mminishell$ \e[m"); 
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
}
