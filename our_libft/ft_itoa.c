/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:16:11 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/26 18:52:00 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countnb(long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		nb = -nb;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		len++;
	}
	return (len + 1);
}

static char	*convertnbr(long nb, int count, char *s)
{
	if (nb == 0)
	{
		s[0] = '0';
		return (s);
	}
	else if (nb < 0)
	{
		nb = -nb;
		s[0] = '-';
	}
	while (nb >= 10)
	{
		s[--count] = (nb % 10) + '0';
		nb /= 10;
	}
	s[--count] = (nb % 10) + '0';
	return (s);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		count;
	char	*str;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		count++;
	}
	count += countnb(nb);
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		return (NULL);
	str = convertnbr(nb, count, str);
	str[count] = '\0';
	return (str);
}
