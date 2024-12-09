/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:37:32 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/09 08:25:13 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	sig_wait(t_lsttoken *token)
{
	int			status;
	t_lsttoken	*current;

	handle_signals(0);
	current = token;
	if (!((g_var.size == 1) && (current->builtin != -1)))
	{
		status = 0;
		while (current)
		{
			waitpid(current->pid, &status, 0);
			current = current->next;
		}
		handle_wait_status(status);
	}
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
