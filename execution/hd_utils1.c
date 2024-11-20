/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:37:38 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/20 13:48:26 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	read_heredoc(t_redir *file, t_name *env, int b)
{
	char	*len;
	// char	*tmp;

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
