/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:36 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/21 14:57:51 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_var			g_var;

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
	g_var.exit_s = 130;
}

static t_name	*init_env(char **en)
{
	t_name	*env;

	env_dup(en);
	if (en && *en)
		env = fill_env(en);
	else
		env = ft_calloc(1, sizeof(t_name));
	return (env);
}

static void	main_loop(t_name *env)
{
	char	*cmd;
	g_var.flag=1;
	
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
}

int	main(int ac, char **av, char **en)
{
	t_name	*env;

	(void)av;
	if (ac != 1)
	{
		write(1, "there is no need for arguments here", 35);
		return (1);
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	env = init_env(en);
	main_loop(env);
	free_env(env);
	rl_clear_history();
	printf("exit\n");
	exit(g_var.exit_s);
}
