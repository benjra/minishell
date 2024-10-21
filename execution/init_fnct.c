/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fnct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:38 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/21 14:15:56 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

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

void	setup_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
