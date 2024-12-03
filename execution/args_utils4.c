/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:57:54 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/02 21:06:05 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	lista_add_front(t_alst **lst, t_alst *new)
{
	if (!new)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

t_alst	*lista_new(void *content)
{
	t_alst	*list;

	list = malloc(sizeof(t_alst));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	validate_cmd(t_lsttoken *token)
{
	if (!token->args[0])
		return ;
	if (ft_strchr(token->args[0], '/'))
		check_cmd_path(token);
	else
		check_command_name(token);
}

char	*get_cmd_path(char *cmd, char **exec_programs_dirs)
{
	char	*cmd_path;
	char	*temp;
	int		i;
	int		status;

	i = -1;
	status = 1;
	cmd_path = NULL;
	temp = NULL;
	while (exec_programs_dirs[++i] && cmd && cmd[0] && status)
	{
		if (cmd_path)
			free(cmd_path);
		temp = ft_strjoin(exec_programs_dirs[i], "/");
		cmd_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(cmd_path, F_OK))
			status = 1;
		else if (access(cmd_path, X_OK))
			status = 2;
		else
			status = 0;
	}
	return (put_cmd_status(status, cmd_path, cmd));
}

void	files_redirections(t_lsttoken *token, int builtin)
{
	t_redir	*curr_red;
	int		b;

	curr_red = token->redirections;
	while (curr_red)
	{
		if (check_file_errors(curr_red->red, builtin))
			break ;
		if (!check_path(curr_red->red, builtin))
			break ;
		if (curr_red->type == 3)
			in_file_prep(token, curr_red->red, builtin);
		else if (curr_red->type == 4)
			out_file_prep(token, curr_red->red, builtin);
		else if (curr_red->type == 5)
			append_file_prep(token, curr_red->red, builtin);
		else if (curr_red->type == 6)
		{
			b = open(g_var.fd, O_RDONLY);
			dup2(b, 0);
			close(b);
		}
		curr_red = curr_red->next;
	}
}
