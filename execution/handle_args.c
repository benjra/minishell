/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:18:57 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/12 16:51:07 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	child_process(t_lsttoken *token, int btn, t_name *env)
{
	g_var.last_child_id = fork();
	if (g_var.last_child_id == -1)
	{
		perror("");
		exit(1);
	}
	if (g_var.last_child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (g_var.pre_pipe_infd != -1)
			dup2(g_var.pre_pipe_infd, STDIN_FILENO);
		if (token->pipe_fd[1] > 2)
			dup2(token->pipe_fd[1], STDOUT_FILENO);
		if (g_var.pre_pipe_infd > 2)
			close(g_var.pre_pipe_infd);
		if (token->pipe_fd[0] > 2)
			close(token->pipe_fd[0]);
		if (token->pipe_fd[1] > 2)
			close(token->pipe_fd[1]);
		handle_file_redirections(token, btn);
		execs(token, btn, env);
	}
	else if (g_var.last_child_id > 0)
		token->pid = g_var.last_child_id;
}

void	execs(t_lsttoken *token, int btn, t_name *env)
{
	if (btn != -1)
	{
		exec_builtin(btn, token, env);
		free_env_array(g_var.envp);
		free_env(g_var.env);
		free_all(g_var.token);
		ft_malloc(0, -1);
		exit(g_var.exit_s);
	}
	else if (token->cmd_path)
	{
		if (execve(token->cmd_path, token->args, g_var.envp) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			free_env_array(g_var.envp);
			free_env(g_var.env);
			free_all(g_var.token);
			ft_malloc(0, -1);
			exit(errno);
		}
	}
	else
		exit(0);
}

static int	init_execute_args(void)
{
	g_var.exit_s = 0;
	g_var.red_builtin = 0;
	g_var.interactive = 0;
	g_var.pre_pipe_infd = -1;
	g_var.fd = NULL;
	signal(SIGINT, SIG_IGN);
	return (0);
}

static void	cleanup_execute_args(t_lsttoken *token)
{
	if (g_var.pre_pipe_infd > 2)
		close(g_var.pre_pipe_infd);
	sig_wait(token);
}

void	execute_args(t_lsttoken *token, t_name *env)
{
	int			i;
	t_lsttoken	*current;

	if (!token)
		return ;
	init_execute_args();
	i = 0;
	current = token;
	while (current && g_var.exit_s == 0)
	{
		if (ft_heredoc(i, current, env))
		{
			if (g_var.fd)
				unlink(g_var.fd);
			free(g_var.fd);
			return ;
		}
		execute_pipes(current, i, env);
		current = current->next;
		i++;
		free(g_var.fd);
	}
	cleanup_execute_args(token);
}
