/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:10 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/15 18:30:24 by assia            ###   ########.fr       */
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
		{
			replace = ft_strdup("$");
			return (replace);
		}
		if (ft_strncmp(temp->name, var, ft_strlen(var)) == 0)
		{
			replace = ft_strdup(temp->value);
			return (replace);
		}
		else if (ft_strncmp("?", var, ft_strlen(var)) == 0)
		{
			replace = ft_strdup(ft_itoa(g_var.exit_s));
			return (replace);
		}
		temp = temp->next;
	}
	return (ft_strdup(""));//
}
