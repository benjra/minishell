/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:37:32 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/15 10:52:26 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	sig_wait(t_lsttoken *token)
{
	int			status;
	t_lsttoken	*current;

	handle_signals(0);
	current = token;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		current = current->next;
	}
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
	handle_signals(1);
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

char	*hdfile(int i)
{
	char	*num;
	char	*name;

	num = ft_itoa(i);
	if (!num)
		return (NULL);
	name = ft_strjoin("file", num);
	free(num);
	if (!name)
		return (NULL);
	return (name);
}

void	hd_sigint(int sig)
{
	(void)sig;
	free_env_array(g_var.envp);
	rl_clear_history();
	exit(130);
}

void	handle_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
}
