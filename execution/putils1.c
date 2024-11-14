/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:52:00 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/13 10:56:13 by amabchou         ###   ########.fr       */
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
	// int	fd;

	files_redirections(token, btn != -1);
	if (btn == -1)
		validate_cmd(token);
	else if (g_var.pre_pipe_infd != -1 && !token->in_fd_set)
		dup2(g_var.pre_pipe_infd, 0);
}
