/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:03 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/29 11:27:23 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	freelist1(t_token *list)
{
	t_token	*temp;

	while (list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp->value);
		free(temp);
	}
}

void	free_env(t_name *env)
{
	t_name	*current;
	t_name	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->name);
		if (current->value) // Only free value if it exists
			free(current->value);
		free(current);
		current = next;
	}
}

// void	free_env(t_name *env)
// {
// 	t_name	*temp;

// 	while (env != NULL)
// 	{
// 		temp = env;
// 		env = env->next;
// 		free(temp->name);
// 		free(temp->value);
// 		free(temp);
// 	}
// }
