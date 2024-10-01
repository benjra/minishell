/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:49 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/01 12:24:23 by assia            ###   ########.fr       */
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
int	countwrd(char *str)
{
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			i++;
			while (str[i] && !(str[i] == '"' || str[i] == '\''))
				i++;
			if (str[i])
				i++;
		}
		else if (is_space(str[i]) || str[i] == '\0')
		{
			len++;
			while (str[i] && is_space(str[i]))
				i++;
		}
		else if (str[i])
			i++;
	}
	return (len + 1);
}

// this fun it split the commonde based on spaces and it skipp the spaces inside quotes
char	**split_string(char *str, int *count)
{
	char **tokens;
	int token_count;
	char c;
	char *start;
	char *token;
	size_t len;
	int length = (countwrd(str) + 1);

	tokens = malloc((length) * sizeof(char *));
	token_count = 0;
	start = str;
	if (!str || !*str)
		return (NULL);
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			c = *str++;
			while (*str && *str != c)
				str++;
			if (*str == c)
				str++;
			if (start != str)
			{
				len = str - start;
				token = malloc(len + 1);
				ft_strncpy(token, start, len);
				token[len] = '\0';
				tokens[token_count++] = token;
			}
			start = str + 1;
		}
		else if (is_space(*str))
		{
			if (start != str)
			{
				len = str - start;
				token = malloc(len + 1);
				ft_strncpy(token, start, len);
				token[len] = '\0';
				tokens[token_count++] = token;
			}
			start = str + 1;
		}
		if (*str)
			str++;
	}
	if (start != str)
	{
		len = str - start + 1;
		if (len > 0)
		{
			token = malloc(len + 1);
			ft_strncpy(token, start, len);
			token[len] = '\0';
			tokens[token_count++] = token;
		}
	}
	tokens[token_count] = NULL;//heap buffer overflow here
	*count = token_count;
	return (tokens);
}

void	free_tokens(char **tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
