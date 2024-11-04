/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:46:52 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/04 17:06:11 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_symbol_token(t_token **list, char *str, char *c, int type)
{
	char	*new;

	new = ft_strnstr(str, c, -1);
	if (new)
	{
		*new = '\0';
		if (*(str))
			check_symbols(str, list);
		lstadd_backs(list, lstnews(type, ft_strdup(c)));
		new += ft_strlen(c);
		if (*new)
			check_symbols(new, list);
	}
}

void	handle_no_symbol_token(t_token **list, char *str, char *c)
{
	int	last;
	int	i;

	last = 0;
	i = 0;
	if (!ft_strncmp(str, c, ft_strlen(c)))
	{
		while (ft_strnstr(str + last, c, ft_strlen(c)) != NULL)
			last++;
		lstadd_backs(list, lstnews(get_type(str), ft_substr(str, i, last)));
	}
	else
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
}

void	parse_and_add_token(t_token **list, char *str, char *c, int type)
{
	char	*new;

	new = NULL;
	new = ft_strchr_skip_quotes(str, c);
	if (new && ft_strnstr(str, c, ft_strlen(str)) != NULL)
		handle_symbol_token(list, str, c, type);
	else
		handle_no_symbol_token(list, str, c);
}
