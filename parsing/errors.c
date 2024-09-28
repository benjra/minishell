/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/28 18:46:40 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	double_symb(t_token *list)
// this function handle the double symbol inside a commande
{
	t_token *tmp;
	int typo;
	int nextp;

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

int	handle_quotes(t_token *list)
// this function handle if the clos quotes exist or not
{
	t_token *tmp;
	int quote_exist;

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

void	ft_ambigious(t_lsttoken *list)
{
	t_lsttoken	*temp;
	int			ambigius;

	temp = list;
	ambigius = 0;
	while (temp)
	{
		while (temp->redirections)
		{
			if (temp->redirections->type == 5 && !*(temp->redirections->red))
				ambigius = 1;
			else if (temp->redirections->type == 6
				&& !*(temp->redirections->red))
				ambigius = 1;
			else if (temp->redirections->type == 3
				&& !*(temp->redirections->red))
				ambigius = 1;
			else if (temp->redirections->type == 4
				&& !*(temp->redirections->red))
				ambigius = 1;
			temp->redirections = temp->redirections->next;
		}
		temp = temp->next;
	}
	if (ambigius == 1)
	{
		gl_var = 1;
		ft_putendl_fd("ambigious redirect!\n", 2);
		return ;
	}
}

int	printf_err(t_token *list) // this function for handle syntax errors
{
	if (pipes_err(list) == 1)
	{
		gl_var = 2;
		ft_putendl_fd("syntax error!", 2);
		return (1);
	}
	if (pipes_err(list) == 2 || double_symb(list) == 1
		|| handle_quotes(list) == 1)
	{
		gl_var = 2; // why it doesnt work
		ft_putendl_fd("syntax error!", 2);
		return (1);
	}
	// if(ft_ambigious(list)==1)
	// {
	// 	gl_var=1;
	// 	ft_putendl_fd("ambigious  redirect!", 2);
	// 	return (1);
	// }
	return (0);
}
