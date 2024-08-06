/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/06 15:10:09 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// two case in ambiguis errors when
// $var doesnt exist ==null
// or when we export a variable like $var="ac ch" found space inside

// should handle all syntax errors
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
			// this case "ls <| ls" it return 0 in this case why ?
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

int qoute(char *str)
{
	int i;
	char c;
	
	i = 0;
	while(str[i])
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
int	pipes_err(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	if (list->type == 2)
		return (1);
	if (tails(list)->type == 2 || tails(list)->type == 3
		|| tails(list)->type == 4 || tails(list)->type == 5
		|| tails(list)->type == 6)
		return (2);
	while (tmp != NULL)
	{
		if (tmp->type == 2 && (!tmp->next || tmp->next->type == 2))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_quotes(t_token *list)
{
	t_token	*tmp;
	// int		i;
	// char	*first_quote;
	int quote_exist;
	
	quote_exist=0;
	tmp = list;
	while (tmp && quote_exist==0)
	{
		if (qoute(tmp->value))
		{
			ft_putendl_fd("syntax error!", 2);
			return(1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	printf_err(t_token *list)
{
	printf("%d\n", double_symb(list));
	if (pipes_err(list) == 1)
		printf("error near `|' \n");
	if (pipes_err(list) == 2 || double_symb(list) == 1
		|| handle_quotes(list) == 1)
		printf("syntax error! \n");
}
