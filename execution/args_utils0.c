/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:55:28 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/20 09:32:28 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	exec_builtin(int btn, t_lsttoken *token, t_name *env)
{
	if (btn == 1 && !g_var.red_error)
		my_cd(env, token->args);
	else if (btn == 2 && !g_var.red_error)
		my_echo(token->args);
	else if (btn == 3 && !g_var.red_error)
		my_env(env, token->args);
	else if (btn == 4 && !g_var.red_error)
		my_exit(token->args, token);
	else if (btn == 5 && !g_var.red_error)
		my_export(&env, token->args);
	else if (btn == 6 && !g_var.red_error)
		my_pwd(env, token->args);
	else if (btn == 7 && !g_var.red_error)
		my_unset(&env, token->args);
	if (g_var.out_fd > 2)
		close(g_var.out_fd);
	g_var.out_fd = 1;
}

int	check_builtin(t_lsttoken *token)
{
	if (!ft_strcmp("cd", token->args[0]))
		return (1);
	else if (!ft_strcmp("echo", token->args[0]))
		return (2);
	else if (!ft_strcmp("env", token->args[0]))
		return (3);
	else if (!ft_strcmp("exit", token->args[0]))
		return (4);
	else if (!ft_strcmp("export", token->args[0]))
		return (5);
	else if (!ft_strcmp("pwd", token->args[0]))
		return (6);
	else if (!ft_strcmp("unset", token->args[0]))
		return (7);
	else
		// return 0;
		return (-1);
}

void	handle_file_descriptors(t_lsttoken *token)
{
	if (token->pipe_fd[1] > 2)
		close(token->pipe_fd[1]);
	if (g_var.pre_pipe_infd > 2)
		close(g_var.pre_pipe_infd);
	g_var.pre_pipe_infd = token->pipe_fd[0];
}

void	handle_pipe_creation(t_lsttoken *token, int pipe_nb)
{
	if (g_var.size != pipe_nb + 1)
	{
		if (pipe(token->pipe_fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
	}
	else
	{
		token->pipe_fd[0] = 0;
		token->pipe_fd[1] = 0;
	}
}

void	execute_pipes(t_lsttoken *token, int pipe_nb, t_name *env)
{
	g_var.btn = check_builtin(token);
	// printf("g_var.size: %d, g_var.btn: %d\n", g_var.size, g_var.btn);
	if (g_var.size == 1 && g_var.btn != -1)
	{
		files_redirections(token, 1);
		exec_builtin(g_var.btn, token, env);
	}
	else
	{
		handle_pipe_creation(token, pipe_nb);
		child_process(token, g_var.btn, env);
		handle_file_descriptors(token);
	}
}
