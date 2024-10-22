/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/21 21:09:35 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	program_name(char **en)
{
	t_name	*env;
	char	*cmd;
	
	
	if (en && *en)
		env = fill_env(en);
	else
		env = ft_calloc(1, sizeof(t_name));
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
			exit(g_var.exit_s);
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
