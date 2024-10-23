/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bouchrabenjraife07@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:34:33 by bbenjrai          #+#    #+#             */
/*   Updated: 2023/11/24 11:57:07 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= len)
		i++;
	if (i >= len)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[len]) && len >= 0)
		len--;
	str = malloc((len - i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)&s1[i], len - i + 2);
	return (str);
}
