/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:03:00 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/07 20:41:00 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	quote(const char **haystack)
{
	char	c;

	c = **haystack;
	(*haystack)++;
	while (**haystack && **haystack != c)
		(*haystack)++;
	if (**haystack == c)
		(*haystack)++;
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
			quote(&haystack + i);
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
