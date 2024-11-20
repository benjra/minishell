/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:10 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/20 19:25:03 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_env(t_name *env, char *var)
{
	t_name	*temp;
	char	*replace;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, var, ft_strlen(var)) == 0
			&& ft_strlen(var) == 0)
			return (ft_strdup("$"));
		if (ft_strncmp(temp->name, var, -1) == 0)
		{
			replace = ft_strdup(temp->value);
			return (replace);
		}
		else if (ft_strncmp("?", var, ft_strlen(var)) == 0)
		{
			replace = ft_itoa(g_var.exit_s);
			return (replace);
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}

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
