/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fnct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:15:17 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 18:23:08 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*setup_heredoc_filename(int id)
{
	char	*id_str;
	char	*filename;

	id_str = ft_itoa(id);
	if (!id_str)
		return (NULL);
	filename = ft_strjoin("/tmp/heredoc_file", id_str);
	free(id_str);
	return (filename);
}

void	process_heredoc_redirections(t_lsttoken *token)
{
	t_redir	*current_redir;

	signal(SIGINT, hd_sigint);
	current_redir = token->redirections;
	while (current_redir)
	{
		read_herdoc(current_redir->red);
		current_redir = current_redir->next;
	}
	exit(0);
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

char	*handle_dollar_cases(char *target, char *output, int flag, int *i)
{
	char	*temp;

	if (target[*i + 1] == '?')
	{
		temp = ft_itoa(g_var.exit_s);
		output = ft_strjoin(output, exit_status(temp, i));
		free(temp);
	}
	else if (!ft_isalnum(target[*i + 1]) && target[*i + 1] != '_')
		output = ft_strjoin(output, special_cases(target, i));
	else if (ft_isdigit(target[*i + 1]) == 1)
		output = ft_strjoin(output, digit(target, i));
	else
		output = ft_strjoin(output, gotta_expand(target, flag, i));
	return (output);
}
