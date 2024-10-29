/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:53:31 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/29 11:49:52 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (const char)c)
	{
		if (s[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((char *)s + i);
}
