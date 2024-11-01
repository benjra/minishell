/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:17:13 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:22:47 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*get_env_in_herdoc(char *target, int flag, char *delimiter)
{
	int		i;
	char	*output;
	int		y21n;

	output = my_dup("");
	i = 0;
	while ((size_t)i < ft_strlen(target))
	{
		y21n = should_not_be_expanded(delimiter);
		if (target[i] == '$' && y21n != 1)
		{
			if (target[i + 1] == '?')
				output = ft_strjoin(output, exit_status(ft_itoa(g_var.exit_s),
							&i));
			else if (!ft_isalnum(target[i + 1]) && target[i + 1] != '_')
				output = ft_strjoin(output, special_cases(target, &i));
			else if (ft_isdigit(target[i + 1]) == 1)
				output = ft_strjoin(output, digit(target, &i));
			else
				output = ft_strjoin(output, gotta_expand(target, flag, &i));
		}
		else
			output = ft_strjoin(output, just_copy(target, &i));
	}
	return (output);
}

void	read_herdoc(char *delimiter)
{
	char	*line;
	char	*without_d_s;
	char	*expand;
	int		fd;

	fd = open_heredoc_file(0);
	line = readline("> ");
	without_d_s = r_quotes(my_dup(delimiter));
	expand = NULL;
	while (!line || ft_strcmp(line, without_d_s))
	{
		if (line)
		{
			expand = get_env_in_herdoc(line, 0, delimiter);
			write(fd, expand, ft_strlen(expand));
			write(fd, "\n", 1);
			free_str(expand);
		}
		else
			break ;
		line = readline("> ");
	}
	free_str(line);
	if (fd > 2)
		close(fd);
}

void	my_heredoc(t_lsttoken *token)
{
	int		id;
	t_redir	*current_redir;

	id = ffork();
	if (id != 0)
		g_var.heredoc_file = ft_strjoin("/tmp/heredoc_file", ft_itoa(id));
	else
		exit(0);
	id = ffork();
	if (id == 0)
	{
		signal(SIGINT, hd_sigint);
		current_redir = token->redirections;
		while (current_redir)
		{
			read_herdoc(current_redir->red);
			current_redir = current_redir->next;
		}
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(id, &g_var.exit_s, 0);
	signal(SIGINT, handler);
}

void	mini_heredoc(t_lsttoken *token, t_name *env)
{
	t_lsttoken	*current;
	int			i;

	if (!token)
		return ;
	current = token;
	i = 0;
	while (current)
	{
		g_var.exit_s = 0;
		if (current->is_heredoc)
		{
			g_var.pre_pipe_infd = -1;
			if (i > 0)
				g_var.pre_pipe_infd = current->previous->pipe_fd[0];
			my_heredoc(current);
			if (g_var.exit_s)
				break ;
			execute_pipes(current, i, env);
		}
		current = current->next;
		i++;
	}
}

void	execute_args(t_lsttoken *token, t_name *env)
{
	int			i;
	t_lsttoken	*current;

	g_var.exit_s = 0;
	g_var.interactive = 0;
	g_var.pre_pipe_infd = -1;
	if (!token)
		return ;
	mini_heredoc(token, env);
	i = 0;
	current = token;
	while (current && g_var.exit_s == 0)
	{
		if (!current->is_heredoc)
		{
			execute_pipes(current, i, env);
		}
		current = current->next;
		i++;
	}
	if (g_var.pre_pipe_infd > 2)
		close(g_var.pre_pipe_infd);
	sig_wait(token);
}
