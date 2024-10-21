/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:47 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/21 14:18:32 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*special_cases(char *target, int *i)
{
	char	*output;
	char	*variable;

	output = "";
	if (target[(*i)] == '$' && (target[(*i) + 1] == '\"'
			|| target[(*i) + 1] == '\''))
		(*i)++;
	variable = until_dollar(&target[(*i)]);
	output = ft_strjoin(output, variable);
	(*i) += ft_strlen(variable);
	return (output);
}

void	lista_add_front(t_alst **lst, t_alst *new)
{
	if (!new)
		return ;
	if (*lst)
		new->next = *lst;
	*lst = new;
}

t_alst	*lista_new(void *content)
{
	t_alst	*list;

	list = malloc(sizeof(t_alst));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

void	hd_sigint(int sig)
{
	(void)sig;
	exit(1);
}

int	upto(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			break ;
	}
	return (i);
}
