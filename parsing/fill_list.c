/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:25 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/23 14:47:21 by bbenjrai         ###   ########.fr       */
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

char	*ft_strnstr1(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	c;
	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] && len > i)
	{
		if (haystack[i]  == '\'' || haystack[i] == '"')
		{
			c = haystack[i++];
			while (haystack[i] && haystack[i] != c)
				i++;
			if (haystack[i] == c)
				i++;
			if (!haystack[i])
				return (NULL);
			
		}	
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
			{
				return ((char *)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}

void	check_symbols(char *str, t_token **list)
{
	if (ft_strnstr1(str, ">>", -1) && ft_strncmp(str, ">>", -1))
		parse_and_add_token(list, str, ">>", 5);
	else if (ft_strnstr1(str, "<<", -1) && ft_strncmp(str, "<<", -1))
		parse_and_add_token(list, str, "<<", 6);
	else if (ft_strnstr1(str, "|", -1) && ft_strncmp(str, "|", -1))
		parse_and_add_token(list, str, "|", 2);
	else if (ft_strnstr1(str, "<", -1) && ft_strncmp(str, "<", -1) && ft_strncmp(str,
			"<<", -1))
		parse_and_add_token(list, str, "<", 3);
	else if (ft_strnstr1(str, ">", -1) && ft_strncmp(str, ">", -1) && ft_strncmp(str,
			">>", -1))
		parse_and_add_token(list, str, ">", 4);
	else
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
}

char	*ft_strchr_skip_quotes(const char *str, char *c)
{
	char	in_quotes;
	int		i;
	int		end;

	i = 0;
	end = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			in_quotes = *str;
			while (*str++ && *str != in_quotes)
			{
				str++;
				end++;
				if (*str == in_quotes)
					return (ft_substr(str, i, end));
			}
		}
		else if (ft_strncmp(str, c, ft_strlen(c)) && *str != in_quotes)
			return ((char *)str);
		str++;
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
			check_symbols( lst[i],&list);
		else
			lstadd_backs(&list, lstnews(1, ft_strdup(lst[i])));
		i++;
	}
	return (list);
}
