/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:44:32 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/26 16:22:55 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
int	handle_quotes_word(char *str, int *last, char *c, int flag)
{
	if (str[*last] == '\'' || str[*last] == '\"')
	{
		if (!flag)
			return (1);
		*c = str[*last];
		(*last)++;
		while (str[*last] && str[*last] != *c)
			(*last)++;
		if (str[*last])
			(*last)++;
		return (1);
	}
	return (0);
}

int	handle_dollar(char *str, int *last)
{
	if (str[*last] == '$')
	{
		(*last)++;
		if (str[*last] == '\'' || str[*last] == '"')
		{
			ft_memmove(str + (*last - 1), str + *last, ft_strlen(str + *last)
				+ 1);
			return (1);
		}
		if (str[*last] && (str[*last] == '?' || ft_isdigit(str[*last])))
		{
			(*last)++;
			return (1);
		}
		while (str[*last] && (ft_isalnum(str[*last]) || str[*last] == '_'
				|| str[*last] == '?'))
			(*last)++;
		return (1);
	}
	return (0);
}

char	*get_word(char *str, int *i)
{
	char	c;
	int		last;
	char	*res;
	int		flag;

	flag = 0;
	c = 0;
	last = *i;
	if (!str)
		return (ft_strdup(""));
	if (str[last] == '\'' || str[last] == '\"')
		flag = 1;
	while (str[last])
	{
		if (handle_quotes_word(str, &last, &c, flag) || handle_dollar(str, &last))
		{
			if (last != *i)
				break ;
		}
		else
		{
			last++;
		}
	}
	res = ft_substr(str, *i, last - *i);
	*i = last;
	return (res);
}
