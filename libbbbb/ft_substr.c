/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:15:01 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/26 18:55:54 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (start + i < ft_strlen(s) && s[i] && i < len)
		i++;
	substring = malloc((i + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len && ft_strlen((char *)s) > start + i)
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}
