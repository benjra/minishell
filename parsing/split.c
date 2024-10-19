/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:49 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/15 18:44:39 by assia            ###   ########.fr       */
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

void	skip_quotes(char **str)
{
	char	c;

	if (**str == '"' || **str == '\'')
	{
		c = **str;
		(*str)++;
		while (**str && **str != c)
			(*str)++;
		if (**str == c)
			(*str)++;
	}
}

void	add_token(char **tokens, char *start, char *str, int *token_count)
{
	int		len;
	char	*token;

	len = str - start;
	if (len > 0)
	{
		token = malloc(len + 1);
		ft_strncpy(token, start, len);
		token[len] = '\0';
		tokens[(*token_count)++] = token;
	}
}

void	process_split(char **tokens, char *str, int *token_count)
{
	char	*start;

	start = str;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			skip_quotes(&str);
		else if (!*str || is_space(*str))
		{
			if (start != str)
				add_token(tokens, start, str, token_count);
			start = str + 1;
			if (*str)
				str++;
		}
		else
			str++;
	}
	if (start != str)
		add_token(tokens, start, str, token_count);
}

char	**split_string(char *str)
{
	char	**tokens;
	int		token_count;
	int		length;

	token_count = 0;
	length = countwrd(str) + 1;
	if (!str || !*str)
		return (NULL);
	tokens = malloc(length * sizeof(char *));
	if (!tokens)
		return (NULL);
	process_split(tokens, str, &token_count);
	tokens[token_count] = NULL;
	return (tokens);
}
