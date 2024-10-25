/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:44:32 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/25 20:52:57 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_word(char *str, int *i)
{
	char	c;
	char	*res;
	int		last;

	c = 0;
	last = *i;
	if (!str)
		return (ft_strdup(""));
	while (str[last])
	{
		if (str[last] == '\'' || str[last] == '\"')
		{
			if (last != *i)
				break;
			c = str[last++];
			while (str[last] && (str[last] != c))
				last++;
			if (str[last])
				last++;
			break ;
		}
		else if (str[last] == '$')
		{
			if (last != *i)
				break;
			if (str[last + 1] == '\'' || str[last + 1] == '"')
			{
				ft_memmove(str +last, str+ last + 1, ft_strlen(str + last + 1)+1);
				break ;
			}
			last++;
			if (str[last] && (str[last] == '?' || ft_isdigit(str[last])))
			{
				last++;
				break ;
			}
			while (str[last] && (ft_isalnum(str[last]) || str[last] == '_'
					|| str[last] == '?'))
			{
				last++;
			}
			break ;
		}
		else
			last++;
			
	}
	res = ft_substr(str, *i, last - *i);
	*i = last;
	return (res);
}
