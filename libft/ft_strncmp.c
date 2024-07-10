/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:49:55 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/24 11:50:55 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while ((s2[i] || s1[i]) && i < n)
		{
			if (s1[i] != s2[i])
			{
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			}
			i++;
		}
	}
	return (0);
}
