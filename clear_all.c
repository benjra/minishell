/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 11:16:19 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/11 11:27:59 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
void free_arg(char **args)
{
    char **temp=args;
    int i=0;
    while(temp[i])
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
		// free(temp->type);
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
		// free(temp->type);
		free_red(temp->redirections);
        free_arg(temp->args);
		free(temp);
	}
}