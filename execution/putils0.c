/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putils0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 08:51:54 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/14 10:49:54 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

int	count_heredoc(t_lsttoken *token)
{
	int count = 0;
	t_redir *file;
	
	file = token->redirections;
	while (file)
	{
		if (file->type == 6)
			count++;
		file = file->next;
	}
	return count;
}

void	free_heredoc(int exit_s, char *s, t_name *env, t_lsttoken *token)
{
	if (s)
		ft_putstr_fd(s, 1);
	free_env(env);
	free(g_var.alist);
	free_all(token);
	rl_clear_history();
	exit(exit_s);
}

int	wait_heredoc(int pid)
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

int	ft_heredoc(int i,t_lsttoken *token, t_name *env)
{
	char	*len;
	t_redir *file;
	char 	*name;
	int 	b;
	int		id;
	char	*num;

	file = token->redirections;
	if (count_heredoc(token) > 16)
		free_heredoc(2, "Max number of heredocs has been exceeded", env, token);
	while (file)
	{
		if (file->type == 6)
		{
			num = ft_itoa(i);
			if (!num)
				return (1);
			name =ft_strjoin("file",num);
			free(num);
			if (!name)
				return (1);
			id = ffork();
			if (id == 0)
			{
				signal(SIGINT, hd_sigint);
				b = open (name,O_RDWR | O_CREAT | O_TRUNC, 0777);
				while ((len = readline("> ")))
				{
					if (!ft_strcmp(len,file->red))
					{
						free(len);
						close (b);
						exit (1);
					}
					len = ft_strjoin(len,"\n");
					write(b,len,ft_strlen (len));
					free(len);
				}
				close (b);
			}
			if (wait_heredoc(id))
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

void	execute_args(t_lsttoken *token, t_name *env)
{
	int			i;
	t_lsttoken	*current;
	int			j;

	g_var.exit_s = 0;
	g_var.interactive = 0;
	g_var.pre_pipe_infd = -1;
	if (!token)
		return ;
	i = 0;
	g_var.fd = NULL;
	current = token;
	g_var.hd_files = ft_calloc(17, sizeof(char *));
	if (!g_var.hd_files)
		return ;
	signal(SIGINT, SIG_IGN);
	while (current && g_var.exit_s == 0)
	{
		if (ft_heredoc(i,current,env))
		{
			if (g_var.fd)
				unlink(g_var.fd);
			return ;
		}
		g_var.hd_files[i] = g_var.fd;
		execute_pipes(current, i, env);
		current = current->next;
		i++;
	}
	if (g_var.pre_pipe_infd > 2)
		close(g_var.pre_pipe_infd);
	if (g_var.btn == -1)
		sig_wait(token);
	j = 0;
	while (g_var.hd_files[j] && j < i)
	{
		if (g_var.hd_files[j])
		{	
			unlink(g_var.hd_files[j]);
			// free(g_var.hd_files[j]);
		}
		j++;
	}
	free(g_var.hd_files);
}
