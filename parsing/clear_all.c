/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:16:19 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/26 16:20:46 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_arg(char **args)
{
	char	**temp;
	int		i;

	temp = args;
	i = 0;
	if (!temp)
		return ;
	while (temp[i])
	{
		free(temp[i++]);
	}
	free(args);
}

void	free_red(t_redir *redi)
{
	t_redir	*temp;

	while (redi != NULL)
	{
		temp = redi;
		redi = redi->next;
		free(temp->red);
		free(temp);
	}
}

void	free_all(t_lsttoken *token)
{
	t_lsttoken	*temp;

	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free_red(temp->redirections);
		free_arg(temp->args);
		free(temp);
	}
}

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
	t_name	*temp;

	while (env != NULL)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}
