/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:55:22 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/06 12:59:30 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*allocate_folders(char *path, int i)
{
	char	*folders;

	folders = malloc(i + 2);
	if (!folders)
	{
		perror("");
		exit(errno);
	}
	lista_add_front(g_var.alist, lista_new(folders));
	my_strncpy(folders, path, i + 1);
	return (folders);
}

int	handle_stat_error(char *path, int is_builtin)
{
	ft_putstr_fd("minishell: ", 2);
	perror(path);
	if (is_builtin)
	{
		g_var.red_error = 1;
		g_var.exit_s = 1;
		return (0);
	}
	else
		exit(1);
}

void	handle_file_redirections(t_lsttoken *token, int btn)
{
	files_redirections(token, btn != -1);
	if (btn == -1)
		validate_cmd(token);
	else if (g_var.pre_pipe_infd != -1 && !token->in_fd_set)
		dup2(g_var.pre_pipe_infd, 0);
}

void	init_g_var(t_lsttoken **token)
{
	t_lsttoken	*current;

	g_var.is_heredoc_last = 0;
	g_var.red_error = 0;
	g_var.pre_pipe_infd = -1;
	g_var.last_child_id = 0;
	g_var.size = 0;
	g_var.interactive = 1;
	g_var.out_fd = 1;
	current = *token;
	while (current)
	{
		current->in_fd_set = 0;
		current->out_fd_set = 0;
		current = current->next;
	}
}

char	*put_cmd_status(int status, char *cmd_path, char *cmd)
{
	if (status)
	{
		if (status == 1 && cmd)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": command not found\n", 2);
			free(cmd_path);
			if (g_var.is_expanded != 0 || cmd[0] == '$')
				exit(127);
			exit(0);
		}
		else if (cmd)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": permission denied\n", 2);
			exit(126);
		}
		return (free(cmd_path), NULL);
	}
	else
		return (cmd_path);
}
