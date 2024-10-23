/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 20:00:32 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/29 10:48:13 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (srclen);
	destlen = ft_strlen(dst);
	if (dstsize == 0 || destlen >= dstsize)
	{
		return (srclen + dstsize);
	}
	while (src[i] && destlen + i < dstsize - 1)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (srclen + destlen);
}
