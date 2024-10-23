/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:29:06 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/21 14:29:08 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*handle_quote(char *str, int *len)
{
	char	c;
	int		i;
	char	*substr;

	c = str[*len];
	(*len)++;
	i = *len;
	while (str[*len] && str[*len] != c)
		(*len)++;
	substr = ft_substr(str, i, *len - i);
	if (str[*len] == c)
		(*len)++;
	return (substr);
}

char	*ins_quote(char *str)
{
	int		i;
	int		len;
	char	*res;
	char	*tmp[2];

	res = ft_strdup("");
	i = 0;
	len = 0;
	while (str[len])
	{
		tmp[0] = res;
		if (str[len] == '"' || str[len] == '\'')
			tmp[1] = handle_quote(str, &len);
		else
		{
			i = len;
			// """'hi'   f"
			while (str[len] && str[len] != '"' && str[len] != '\'')
				len++;
			tmp[1] = ft_substr(str, i, len - i);
		}
		res = ft_strjoin(res, tmp[1]);
		free(tmp[1]);
		free(tmp[0]);
	}
	return (res);
}
