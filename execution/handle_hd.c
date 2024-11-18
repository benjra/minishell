/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:21:11 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/18 17:38:11 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

static int	count_heredoc(t_lsttoken *token)
{
	int		count;
	t_redir	*file;

	count = 0;
	file = token->redirections;
	while (file)
	{
		if (file->type == 6)
			count++;
		file = file->next;
	}
	return (count);
}

static int	wait_heredoc(int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if ((status >> 8) == 130)
	{
		write(1, "\n", 2);
		unlink(g_var.fd);
		return (1);
	}
	return (0);
}

static void	handle_heredoc_child(char *name, t_redir *file, t_name *env)
{
	int		b;
	char	*len;

	signal(SIGINT, hd_sigint);
	b = open(name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		len = readline("> ");
		if (!len)
		{
			printf("bash : EOF! \n");
			break ;
		}
		if (!ft_strcmp(len, file->red))
		{
			free(len);
			close(b);
			exit(1);
		}
		len = ft_strjoin(len, "\n");
		if (file->expand)
		{
			len = small_expand__(len, env);
			write(b, len, ft_strlen(len));
		}
		else
			write(b, len, ft_strlen(len));
		// free(len);
	}
	close(b);
	exit(0);
}

static int	handle_fork(char *name, t_redir *file, t_name *env)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		perror("");
		exit(1);
	}
	if (id == 0)
		handle_heredoc_child(name, file, env);
	return (wait_heredoc(id));
}

int	ft_heredoc(int i, t_lsttoken *token, t_name *env)
{
	t_redir	*file;
	char	*name;

	file = token->redirections;
	if (count_heredoc(token) > 16)
		free_heredoc(2, "Max number of heredocs has been exceeded", env, token);
	while (file)
	{
		if (file->type == 6)
		{
			name = hdfile(i);
			if (!name)
				return (1);
			if (handle_fork(name, file, env))
			{
				free(name);
				return (1);
			}
		}
		file = file->next;
	}
	g_var.fd = name;
	return (0);
}
