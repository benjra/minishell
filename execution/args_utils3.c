/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:56:48 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/03 01:39:37 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	in_file_prep(t_lsttoken *token, char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		g_var.exit_s = errno;
		g_var.red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var.size > 1)
			exit(1);
	}
	else
	{
		token->in_fd_set = 1;
		if ((!token->is_heredoc || !g_var.is_heredoc_last) && !is_builtin)
			dup2(fd, 0);
		if (fd > 2)
			close(fd);
	}
}

void	out_file_prep(t_lsttoken *token, char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		g_var.exit_s = errno;
		g_var.red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var.size > 1)
			exit(1);
	}
	else
	{
		token->out_fd_set = 1;
		if (!is_builtin || g_var.size > 1)
		{
			dup2(fd, 1);
			if (fd > 2)
				close(fd);
		}
		else
			g_var.out_fd = fd;
	}
}

void	append_file_prep(t_lsttoken *token, char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		g_var.exit_s = errno;
		g_var.red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var.size > 1)
			exit(1);
	}
	else
	{
		token->out_fd_set = 1;
		if (!is_builtin || g_var.size > 1)
		{
			dup2(fd, 1);
			if (fd > 2)
				close(fd);
		}
		else
			g_var.out_fd = fd;
	}
}

int	check_path(char *path, int is_builtin)
{
	char		*folders;
	struct stat	statbuf;
	int			i;

	if (ft_strchr(path, '/') == 0)
		return (1);
	i = ft_strlen(path);
	while (i != 0 && path[i] != '/')
		i--;
	folders = allocate_folders(path, i);
	if (stat(folders, &statbuf) == -1)
		return (handle_stat_error(path, is_builtin));
	return (1);
}

int	check_file_errors(char *path, int builtin)
{
	ft_putstr_fd(path, 2); //prints my path :)
	ft_putstr_fd("\n", 2);
	if (path && (path[0] == '$' || (path[0] == '"' && path[1] == '$')))
	{
		g_var.red_error = 1;
		g_var.exit_s = 1;
		
		if (path[0] == '$' && path[1])
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(" ambiguous redirect\n", 2);
		}
		else
			ft_putstr_fd("minishell: No such file or directory\n", 2);
		if (builtin)
			return (1);
		else
			exit(1);
	}
	return (0);
}
