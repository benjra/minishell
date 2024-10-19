/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:40:57 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/19 18:54:38 by bbenjrai         ###   ########.fr       */
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
	while (str[last])
	{
		if ((str[last] == '\'' && str[last + 1] == '\''))
			last += 2;
		if (str[last] == '\'' || str[last] == '\"')
		{
			c = str[last++];
			while (str[last] && (str[last] != c))
				last++;
			if (str[last])
				last++;
			break ;
		}
		else
		{
			if (str[last])
			{
				if (str[last] == '$' || !ft_isalnum(str[last]))
					last++;
				if(str[last] && str[last]=='?')
				{
						last++;	
						break;
				}
				while (str[last] && (ft_isalnum(str[last]) || str[last] == '_'
						|| str[last] == '?'))
				{
					last++;
				}
			}
			break ;
		}
	}
	res = ft_substr(str, *i, last - *i);
	*i = last;
	return (res);
}
