/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:41:53 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/26 18:56:51 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	int		i;

	i = 0;
	s = (char *)src;
	d = (char *)dst;
	if ((!d && !s))
		return (NULL);
	if (d == s)
		return (dst);
	while (n-- > 0)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
