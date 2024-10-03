/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/03 20:48:52 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	handle_quotes(t_token *list)
{
	t_token	*tmp;
	int		quote_exist;

	quote_exist = 0;
	tmp = list;
	while (tmp && quote_exist == 0)
	{
		if (qoute(tmp->value))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_ambigious(t_lsttoken *list)
{
	t_lsttoken	*temp;

	temp = list;
	while (temp)
	{
		while (temp->redirections)
		{
			if (temp->redirections->type == 5 && !*(temp->redirections->red))
				return (1);
			else if (temp->redirections->type == 6
				&& !*(temp->redirections->red))
				return (1);
			else if (temp->redirections->type == 3
				&& !*(temp->redirections->red))
				return (1);
			else if (temp->redirections->type == 4
				&& !*(temp->redirections->red))
				return (1);
			temp->redirections = temp->redirections->next;
		}
		temp = temp->next;
	}
	return (0);
}

int	printf_err(t_token *list)
{
	if (pipes_err(list) == 1)
	{
		ex = 2;
		ft_putendl_fd("syntax error!", 2);
		return (1);
	}
	if (pipes_err(list) == 2 || double_symb(list) == 1
		|| handle_quotes(list) == 1)
	{
		ex = 2;
		ft_putendl_fd("syntax error!", 2);
		return (1);
	}
	return (0);
}
