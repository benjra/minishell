/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:36 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/15 18:07:42 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
t_var g_var;

void	env_dup(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_var.envp = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i])
		g_var.envp[i] = ft_strdup(env[i]);
	g_var.envp[i] = NULL;
}
void	handler(int signum)
{
	(void)signum;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var.exit_s= 130;
}

int	main(int ac, char **av, char **en)
{
	(void)av;
	t_name	*env;
	char 	*cmd;

	if (ac != 1)
	{
		write(1, "there is no need for arguments here", 35);
		return (1);
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	env_dup(en);
	if (en && *en)
		env = fill_env(en);
	else
		env = ft_calloc(1, sizeof(t_name));
	while (1)
	{
		cmd = readline("minishell$ ");
		if (!cmd)
			break ;
		else if (ft_strncmp(cmd, "", -1))
		{
			
			add_history(cmd);
			parsing(cmd, env);
		}
		free(cmd);
	}
	free_env(env);
	rl_clear_history();
	printf("exit\n");
	exit(g_var.exit_s);
}
