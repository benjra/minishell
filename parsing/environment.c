/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:10 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/21 13:17:14 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// this function is used for get a variable from the envirement list
// if exist if not it return empty value else if the var=? it return 0


char	*ft_env(t_name *env, char *var)
{
	t_name	*temp;
	char	*replace;

	temp = env;
	if (*var == 14)
		return (ft_strdup(""));
	while (temp)
	{
		// if (ft_strncmp(temp->name, var, ft_strlen(var)) == 0
		// 	&& ft_strlen(var) == 0)
		// 	return (ft_strdup("$"));
		if (ft_strncmp(temp->name, var, -1) == 0)
		{
			replace = ft_strdup(temp->value);
			return (replace);
		}
		else if (ft_strncmp("?", var, ft_strlen(var)) == 0)
		{
			replace = ft_strdup(ft_itoa(gl_ex));//leak
			return (replace);
		}
		temp = temp->next;
	}
	return (ft_strdup(""));
}
