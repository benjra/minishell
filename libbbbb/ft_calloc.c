/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:25:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/30 12:02:39 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if (size != 0 && count >= SIZE_MAX / size)
	{
		return (NULL);
	}
	str = malloc(size * count);
	if (str == 0)
	{
		return (0);
	}
	ft_bzero(str, count * size);
	return (str);
}
