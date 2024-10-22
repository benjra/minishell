/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:27:55 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/05 16:16:19 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	double_symb(t_token *list)
{
	t_token	*tmp;
	int		typo;
	int		nextp;

	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			typo = tmp->type;
			nextp = tmp->next->type;
			if (typo == 3 || typo == 4 || typo == 5 || typo == 6)
			{
				if (nextp == 2 || nextp == 3 || nextp == 4 || nextp == 5
					|| nextp == 6)
					return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	pipes_err(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (list && list->type == 2)
		return (1);
	if (list && (tails(list)->type == 2 || tails(list)->type == 3
			|| tails(list)->type == 4 || tails(list)->type == 5
			|| tails(list)->type == 6))
		return (2);
	while (tmp != NULL)
	{
		if (tmp->type == 2 && (!tmp->next || tmp->next->type == 2))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	qoute(char *str)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && c != str[i])
				i++;
			if (!str[i])
				return (1);
			i++;
		}
		else
			i++;
	}
	return (0);
}
