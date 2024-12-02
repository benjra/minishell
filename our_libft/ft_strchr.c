/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:53:31 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/12/02 20:35:36 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if(!s)
		return NULL;
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
