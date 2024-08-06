/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:25 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/06 11:26:33 by bbenjrai         ###   ########.fr       */
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
			return (5);
	}
	return (1);
}

t_token	*tails(t_token *list)
{
	t_token	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	lstadd_backs(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		tails(*lst)->next = new;
}

t_token	*lstnews(int type, char *value)
{
	t_token	*linked_lst;

	linked_lst = malloc(sizeof(t_token));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
	linked_lst->type = type;
	linked_lst->value = value;
	linked_lst->next = NULL;
	return (linked_lst);
}

void	check_symbols(char *str, t_token **list)
{
	if (ft_strnstr(str, ">>", -1) && ft_strncmp(str, ">>", -1))
		parse_and_add_token(list, str, ">>", 5);
	else if (ft_strnstr(str, "<<", -1) && ft_strncmp(str, "<<", -1))
		parse_and_add_token(list, str, "<<", 6);
	else if (ft_strchr(str, '|') && ft_strncmp(str, "|", -1))
		parse_and_add_token(list, str, "|", 2);
	else if (ft_strchr(str, '<') && ft_strncmp(str, "<", -1) && ft_strncmp(str,
			"<<", -1))
		parse_and_add_token(list, str, "<", 3);
	else if (ft_strchr(str, '>') && ft_strncmp(str, ">", -1) && ft_strncmp(str,
			">>", -1))
		parse_and_add_token(list, str, ">", 4);
	else
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
}

char	*ft_strchr_skip_quotes(const char *str, char *c)
{
	int	in_quotes;

	in_quotes = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			in_quotes = !in_quotes;
		}
		else if (!ft_strncmp(str, c, ft_strlen(c)) && !in_quotes)
		{ // to avoid the cases like when u want to search for an string
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}

void	parse_and_add_token(t_token **list, char *str, char *c, int type)
{
	char	*new;

	new = ft_strchr_skip_quotes(str, c);
	if (new &&ft_strncmp(str, c, -1))
	{
		*new = '\0';
		if (*(str))
		{
			check_symbols(str, list);
		}
		// Check if there's more content after the symbol
		lstadd_backs(list, lstnews(type, ft_strdup(c)));
		new += ft_strlen(c);
		if (*new)
		{
			check_symbols(new, list);
		}
	}
	else if (!new)
	{
		// If no symbol was found, add the whole string as a single token
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
	}
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
		{
			if (ft_strnstr(lst[i], ">>", -1) && ft_strncmp(lst[i], ">>", -1))
				parse_and_add_token(&list, lst[i], ">>", 5);
			else if (ft_strnstr(lst[i], "<<", -1) && ft_strncmp(lst[i], "<<",
					-1))
				parse_and_add_token(&list, lst[i], "<<", 6);
			else if (ft_strchr(lst[i], '|') && ft_strncmp(lst[i], "|", -1))
				parse_and_add_token(&list, lst[i], "|", 2);
			else if (ft_strchr(lst[i], '<') && ft_strncmp(lst[i], "<", -1)
				&& ft_strncmp(lst[i], "<<", -1))
				parse_and_add_token(&list, lst[i], "<", 3);
			else if (ft_strchr(lst[i], '>') && ft_strncmp(lst[i], ">", -1)
				&& ft_strncmp(lst[i], ">>", -1))
				parse_and_add_token(&list, lst[i], ">", 4);
			else
				lstadd_backs(&list, lstnews(get_type(lst[i]),
											ft_strdup(lst[i])));
												// function that gettype
		}
		else
		{
			lstadd_backs(&list, lstnews(1, ft_strdup(lst[i])));
		}
		i++;
	}
	return (list);
}
