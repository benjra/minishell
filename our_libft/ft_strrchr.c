/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:52:28 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/29 11:51:29 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, size_t c)
{
	size_t	flag;
	size_t	len;

	flag = 0;
	len = ft_strlen((char *)s);
	while (flag == 0)
	{
		if (s[len] != (const char)c)
		{
			if (len != 0)
				len--;
			else
				return (0);
		}
		else if (s[len] == (const char)c)
		{
			flag = 1;
		}
	}
	return ((char *)s + len);
}
