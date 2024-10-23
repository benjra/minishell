/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:44:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/28 16:15:26 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	int		i;

	i = len - 1;
	d = (char *)dst;
	s = (char *)src;
	if (d > s)
	{
		while (len-- > 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	else if (d < s)
	{
		i = 0;
		while (len-- > 0)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
