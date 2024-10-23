/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:33:39 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/29 11:53:39 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*st;
	size_t	i;

	i = 0;
	st = (char *)s;
	while (n > i)
	{
		if (st[i] == (char)c)
		{
			return (st + i);
		}
		i++;
	}
	return (NULL);
}
