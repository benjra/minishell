/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:25 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/20 20:48:51 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	get_type(char *lst)
{
	if (ft_strncmp(lst, ">", 1) == 0 || ft_strncmp(lst, "<", 1) == 0
		|| ft_strncmp(lst, "|", 1) == 0 || ft_strncmp(lst, "<<", 2) == 0
		|| ft_strncmp(lst, ">>", 2) == 0)
	{
		if (ft_strncmp(lst, "|", 1) == 0)
			return (TOKEN_PIPE);
		else if (ft_strncmp(lst, "<<", 2) == 0)
			return (TOKEN_REDIR_HEREDOC);
		else if (ft_strncmp(lst, ">>", 2) == 0)
			return (TOKEN_REDIR_APPEND);
		if (ft_strncmp(lst, ">", 1) == 0)
			return (TOKEN_REDIR_OUT);
		else if (ft_strncmp(lst, "<", 1) == 0)
			return (TOKEN_REDIR_IN);
	}
	return (1);
}

void	check_symbols(char *str, t_token **list)
{
	if (ft_strnstr1(str, ">>", -1) && ft_strncmp(str, ">>", -1))
		parse_and_add_token(list, str, ">>", TOKEN_REDIR_APPEND);
	else if (ft_strnstr1(str, "<<", -1) && ft_strncmp(str, "<<", -1))
		parse_and_add_token(list, str, "<<", TOKEN_REDIR_HEREDOC);
	else if (ft_strnstr1(str, "|", -1) && ft_strncmp(str, "|", -1))
		parse_and_add_token(list, str, "|", TOKEN_PIPE);
	else if (ft_strnstr1(str, "<", -1) && ft_strncmp(str, "<", -1)
		&& ft_strncmp(str, "<<", -1))
		parse_and_add_token(list, str, "<", TOKEN_REDIR_IN);
	else if (ft_strnstr1(str, ">", -1) && ft_strncmp(str, ">", -1)
		&& ft_strncmp(str, ">>", -1))
		parse_and_add_token(list, str, ">", TOKEN_REDIR_OUT);
	else
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
}

t_token	*fill_list(char **lst)
{
	int		i;
	t_token	*list;

	i = 0;
	list = NULL;
	while (lst[i])
	{
		if (ft_strchr(lst[i], '|') || ft_strchr(lst[i], '<')
			|| ft_strchr(lst[i], '>'))
			check_symbols(lst[i], &list);
		else
			lstadd_backs(&list, lstnews(TOKEN_WORD, ft_strdup(lst[i])));
		i++;
	}
	return (list);
}
