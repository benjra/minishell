/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:03:00 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/19 14:18:10 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	quote(const char *haystack, size_t *i)
{
	char	c;

	if (!haystack || !haystack[(*i)])
	{
		return (0);
	}
	c = haystack[(*i)];
	(*i)++;
	while (haystack[(*i)] && haystack[(*i)] != c)
		(*i)++;
	if (haystack[(*i)] == c)
		(*i)++;
	return (1);
}

char	*ft_strnstr1(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] && len > i)
	{
		if (haystack[i] == '\'' || haystack[i] == '"')
		{
			quote(haystack, &i);
			if (!haystack[i])
				return (NULL);
		}
		j = 0;
		while (haystack[i + j] && haystack[i + j] == needle[j] && i + j < len)
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strchr1(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != (const char)c)
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			quote(s, &i);
			if (!s[i])
				return (NULL);
		}
		if (s[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((char *)s + i);
}
