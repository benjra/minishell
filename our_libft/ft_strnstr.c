/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:51:46 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/12 10:58:12 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] && len > i)
	{
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
