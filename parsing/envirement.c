/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirement.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:10 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/13 09:15:33 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_env(t_name *env, char *var)//this function is used for get a variable from the envirement list if exist if not it return empty value else if the var=? it return 0
{
	t_name	*temp;
	char	*replace;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->name, var, ft_strlen(var)) == 0)
		{
			replace = ft_strdup(temp->value);
			return (replace);
		}
		else if(ft_strncmp("?",var,ft_strlen(var))==0)
			{
				replace=ft_strdup("0");
				return (replace);
			}
		temp = temp->next;
	}
	return (ft_strdup(""));
}