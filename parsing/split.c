/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:49 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/26 15:26:39 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	add_token(char **tokens, char *start, char *str, int *token_count)
{
	int		len;
	char	*token;

	len = str - start;
	if (len > 0)
	{
		token = malloc(len + 1);
		if (!token)
			free(token);
		ft_strncpy(token, start, len);
		token[len] = '\0';
		tokens[(*token_count)++] = token;
	}
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
