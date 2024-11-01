/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:16:32 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:16:33 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*replace(char *str, char rip)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == rip)
			continue ;
		str[j] = str[i];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*r_quotes(char *str)
{
	int		i;
	int		len;
	char	selected;
	char	rip;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			selected = str[i];
			rip = -1;
			len = upto(&str[i + 1], selected);
			if (str[len + i + 1] == '\0')
				return (NULL);
			str[i] = rip;
			str[len + i + 1] = rip;
			i += len;
		}
	}
	return (replace(str, rip));
}

int	ffork(void)
{
	int	id;

	id = fork();
	if (id == -1)
	{
		perror("");
		exit(1);
	}
	return (id);
}

void	free_str(void *ptr)
{
	if (ptr)
		free(ptr);
}

int	should_not_be_expanded(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			return (1);
		}
		i++;
	}
	return (-1);
}
