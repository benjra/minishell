/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:11 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/12 13:11:16 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	read_heredoc(t_redir *file, t_name *env, int b)
{
	char	*len;

	while (1)
	{
		len = readline("> ");
		if (!len)
		{
			printf("minishell: warning: heredoc delimited by EOF! \n");
			break ;
		}
		if (!ft_strcmp(len, file->red))
		{
			free(len);
			break ;
		}
		len = join_and_expand(len, file, env);
		write(b, len, ft_strlen(len));
		free(len);
	}
}

char	*join_and_expand(char *len, t_redir *file, t_name *env)
{
	char	*tmp;

	tmp = ft_strjoin(len, "\n");
	free(len);
	len = tmp;
	if (!len)
	{
		perror("ft_strjoin");
		freee();
		exit(1);
	}
	if (file->expand)
	{
		len = small_expand__(len, env);
		if (!len)
		{
			perror("small_expand__");
			free_env(g_var.env);
			free_env_array(g_var.envp);
			free_all(g_var.token);
			ft_malloc(0, -1);
			exit(1);
		}
	}
	return (len);
}

void	handle_wait_status(int status)
{
	g_var.exit_s = 128 + WTERMSIG(status);
	if (WTERMSIG(status) + 128 == 130)
	{
		g_var.exit_s = 128 + WTERMSIG(status);
		write(1, "\n", 1);
	}
	else if (WTERMSIG(status) + 128 == 131)
	{
		g_var.exit_s = 128 + WTERMSIG(status);
		write(1, "Quit\n", 6);
	}
	else
		g_var.exit_s = WEXITSTATUS(status);
}

void	my_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	files_redirections_norm(t_lsttoken *token, t_redir *red, int builtin)
{
	int	b;

	if (red->type == 3)
	{
		in_file_prep(token, red->red, builtin);
		if (g_var.red_error)
			return ;
	}
	else if (red->type == 4)
		out_file_prep(token, red->red, builtin);
	else if (red->type == 5)
		append_file_prep(token, red->red, builtin);
	else if (red->type == 6)
	{
		b = open(g_var.fd, O_RDONLY);
		dup2(b, 0);
		close(b);
		if (g_var.fd)
			unlink(g_var.fd);
	}
}
