/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:25 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/19 10:23:36 by assia            ###   ########.fr       */
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
			return (2);
		else if (ft_strncmp(lst, "<<", 2) == 0)
			return (6);
		else if (ft_strncmp(lst, ">>", 2) == 0)
			return (5);
		if (ft_strncmp(lst, ">", 1) == 0)
			return (4);
		else if (ft_strncmp(lst, "<", 1) == 0)
			return (3);
	}
	return (1);
}

void	check_symbols(char *str, t_token **list)
{
	if (ft_strnstr1(str, ">>", -1) && ft_strncmp(str, ">>", -1))
		parse_and_add_token(list, str, ">>", 5);
	else if (ft_strnstr1(str, "<<", -1) && ft_strncmp(str, "<<", -1))
		parse_and_add_token(list, str, "<<", 6);
	else if (ft_strnstr1(str, "|", -1) && ft_strncmp(str, "|", -1))
		parse_and_add_token(list, str, "|", 2);
	else if (ft_strnstr1(str, "<", -1) && ft_strncmp(str, "<", -1)
		&& ft_strncmp(str, "<<", -1))
		parse_and_add_token(list, str, "<", 3);
	else if (ft_strnstr1(str, ">", -1) && ft_strncmp(str, ">", -1)
		&& ft_strncmp(str, ">>", -1))
		parse_and_add_token(list, str, ">", 4);
	else
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
}

char	*ft_strchr_skip_quotes(const char *s, char *c)
{
	int		in_quotes;
	char	quote_char;

	in_quotes = 0;
	quote_char = '\0';
	while (*s)
	{
		if ((*s == '\'' || *s == '\"') && (in_quotes == 0 || *s == quote_char))
		{
			if (in_quotes)
				in_quotes = 0;
			else
			{
				in_quotes = 1;
				quote_char = *s;
			}
		}
		else if (*s == *c && !in_quotes)
			return ((char *)s);
		s++;
	}
	return (NULL);
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
			lstadd_backs(&list, lstnews(1, ft_strdup(lst[i])));
		i++;
	}
	return (list);
}
