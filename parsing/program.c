/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/29 16:57:40 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	program_name(char **en)
// this function is for displaying the promt and read from the readline
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
