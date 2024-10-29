/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:54 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/26 15:25:41 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	len(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (lst->type == 2)
			break ;
		if ((lst->type >= 3 && lst->type <= 6))
		{
			lst = lst->next;
		}
		else
			i++;
		lst = lst->next;
	}
	return (i);
}

int	handle_redirection(t_token **temp, t_lsttoken *token)
{
	t_redir	*redirections;
	char	*tmmp;

	tmmp = NULL;
	if ((*temp)->next != NULL && (*temp)->type > 2 && (*temp)->type <= 6)
	{
		tmmp = ft_strdup((*temp)->next->value);
		redirections = new_red((*temp)->type, tmmp);
		red_addback(&(token->redirections), redirections);
		(*temp) = (*temp)->next;
		return (1);
	}
	return (0);
}

void	add_new_token_node(t_token **temp, t_lsttoken **token, int *i)
{
	add_back(token, newnode((*temp)->type, (*token)->args));
	*token = (*token)->next;
	(*token)->args = ft_calloc(len((*temp)->next) + 1, sizeof(char *));
	(*token)->args[len((*temp)->next)] = NULL;
	(*token)->redirections = NULL;
	*i = 0;
}

t_lsttoken	*init_token(t_token *list)
{
	t_lsttoken	*token;

	token = ft_calloc(1, sizeof(t_lsttoken));
	if (!token)
		return (NULL);
	token->args = malloc((len(list) + 1) * sizeof(char *));
	if (!token->args)
		return (NULL);
	token->args[len(list)] = NULL;
	token->redirections = NULL;
	return (token);
}

t_lsttoken	*fill_token(t_token *list)
{
	t_token		*temp;
	t_lsttoken	*token[2];
	int			i;

	temp = list;
	i = 0;
	token[0] = init_token(list);
	if (!token[0])
		return (NULL);
	token[1] = token[0];
	while (temp != NULL)
	{
		if (handle_redirection(&temp, token[0]))
			(void)0;
		else if ((temp->next != NULL && temp->type == 2))
			add_new_token_node(&temp, &token[0], &i);
		else
		{
			token[0]->args[i++] = ft_strdup(temp->value);
			token[0]->args[i] = NULL;
		}
		if (temp != NULL)
			temp = temp->next;
	}
	return (token[1]);
}
