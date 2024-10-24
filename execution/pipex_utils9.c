/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils9.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:08:01 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/24 01:45:33 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	handle_malloc_error(void)
{
	perror("");
	exit(errno);
}

char	*allocate_folders(char *path, int i)
{
	char	*folders;

	folders = malloc(i + 2);
	if (!folders)
		handle_malloc_error();
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
	int	fd;

	files_redirections(token, btn != -1);
	if (btn == -1)
		validate_cmd(token);
	if (token->is_heredoc && g_var.is_heredoc_last)
	{
		fd = open_heredoc_file(1);
		dup2(fd, 0);
		if (fd > 2)
			close(fd);
	}
	else if (g_var.pre_pipe_infd != -1 && !token->in_fd_set)
		dup2(g_var.pre_pipe_infd, 0);
}

void	handle_pipe_redirections(t_lsttoken *token, int pipe_nb)
{
	if (g_var.size != pipe_nb + 1 && !token->out_fd_set)
		dup2(token->pipe_fd[1], 1);
	if (token->pipe_fd[1] > 2)
		close(token->pipe_fd[1]);
	if (token->pipe_fd[0] > 2)
		close(token->pipe_fd[0]);
}
