/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:36:00 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/04 14:36:50 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	is_space(char str)
{
	if (str == ' ' || str == '\n' || str == '\t' || str == '\v' || str == '\f'
		|| str == '\r')
		return (1);
	return (0);
}

int	skip_quotes_in_count(char *str, int i)
{
	char	c;

	if (str[i] == '"' || str[i] == '\'')
	{
		c = str[i++];
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == c)
			i++;
	}
	return (i);
}

// int	countwrd(char *str)
// {
// 	int	i;
// 	int	len;
// 	int	flag;

// 	i = 0;
// 	len = 0;
// 	flag = 0;
// 	while (str[i])
// 	{
// 		i = skip_quotes_in_count(str, i);
// 		if (is_space(str[i]))
// 		{
// 			len++;
// 			while (str[i] && is_space(str[i]))
// 				i++;
// 		}
// 		else if (str[i++])
// 		{
// 			if (flag == 0)
// 			{
// 				flag = 1;
// 				len++;
// 			}
// 		}
// 	}
// 	return (len);
// }
int    countwrd(char *str)
{
    int    i;
    int    len;
    int flag=0;
    
    i = 0;
    len = 0;
    while (str[i])
    {  
       	i = skip_quotes_in_count(str, i);
        if (is_space(str[i]))
        {
            flag=1;
            len++;
            while (str[i] && !is_space(str[i]))
                i++;
            if (is_space(str[i]))
                i++;
        }
        else if (str[i])
        {
            if(flag==0)
                {
                    flag=1;
                    len++;
                }
            i++;
        }
    }
    return (len );
}
