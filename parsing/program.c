/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/01 12:22:23 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	program_name(char **en)
{
	t_name *env;
	char *cmd;

	env = fill_env(en);
	env->ev = en;
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
		{
			printf("exit\n");
			free_env(env);
			free(cmd);
			rl_clear_history();
			exit(ex); // should use exit_status && free all the variables before
		}
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
