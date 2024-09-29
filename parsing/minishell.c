/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:36 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/29 14:06:07 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// int		gl_var = 0;
int		ex = 0;
void	handler(int signum)
{
	(void)signum;
	write(0, "\n", 1);
	rl_on_new_line(); // its make u to write on newline
	rl_replace_line("", 0);
	// its make u to replace the newline with string input
	rl_redisplay(); // it
	ex = 130;
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
	{
		write(1, "there is no need of arguments here", 35);
		return (1);
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	program_name(env);
}
