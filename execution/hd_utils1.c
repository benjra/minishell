/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 02:19:11 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/09 08:26:40 by assia            ###   ########.fr       */
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
		exit(1);
	}
	if (file->expand)
	{
		len = small_expand__(len, env);
		if (!len)
		{
			perror("small_expand__");
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
