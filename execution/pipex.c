/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:17:13 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 18:23:34 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*get_env_in_heredoc(char *target, int flag, char *delimiter)
{
	int		i;
	char	*output;
	int		y21n;

	i = 0;
	output = my_dup("");
	y21n = should_not_be_expanded(delimiter);
	while ((size_t)i < ft_strlen(target))
	{
		if (target[i] == '$' && y21n != 1)
			output = handle_dollar_cases(target, output, flag, &i);
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
			expand = get_env_in_heredoc(line, 0, delimiter);
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
	int		child_pid;
	char	*filename;

	id = ffork();
	if (id != 0)
	{
		filename = setup_heredoc_filename(id);
		g_var.heredoc_file = filename;
	}
	else
		exit(0);
	child_pid = ffork();
	if (child_pid == 0)
		process_heredoc_redirections(token);
	signal(SIGINT, SIG_IGN);
	waitpid(child_pid, &g_var.exit_s, 0);
	signal(SIGINT, handler);
	free(filename);
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
