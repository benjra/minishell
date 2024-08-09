/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:49 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/09 13:00:15 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#define MAX_TOKENS 100

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
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
	if (str == ' ' || str=='\n' || str=='\t' || str=='\v' || str=='\f' || str=='\r')
		return (1);
	return (0);
}
int countwrd(char *str)
{
    int i = 0;
    int len = 0;
    int in_quotes = 0;

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            in_quotes = !in_quotes;
            i++;
            while (str[i] && !(str[i] == '"' || str[i] == '\''))
                i++;
        }
        if (is_space(str[i]) || str[i] == '\0')
        {
            if (!isspace(str[i - 1]) && !in_quotes)
                len++;
        }
        i++;
    }
    return len + 1;
}

char	**split_string(char *str, int *count)
{
	char	**tokens;
	int		token_count;
	int		in_quotes;
	char	*start;
	char	*token;
	size_t	len;
	int length=(countwrd(str)+ 1);

	tokens = malloc(length * sizeof(char *));//should modify the max tokens
	token_count = 0;
	in_quotes = 0;
	start = str;
	if (!str || !*str)
		return (NULL);
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			in_quotes = !in_quotes;
		}
		else if (is_space(*str) && !in_quotes)
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
		str++;
	}
	if (start != str)
	{
		len = str - start;
		token = malloc(len + 1);
		ft_strncpy(token, start, len);
		token[len] = '\0';
		tokens[token_count++] = token;
	}
	tokens[token_count] = NULL;
	*count = token_count;
	return (tokens);
}

void free_tokens(char **tokens, int count) 
{
    int i = 0; 
    while (i < count) {
        free(tokens[i]);
        i++;
    }
    free(tokens);
}


// size_t	ft_len2(char **s)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	**join2pointer(char **com, char *str)
// {
// 	size_t	len2;
// 	char	**new_com;
// 	int		i;

// 	len2 = ft_len2(com);
// 	new_com = ft_calloc((len2 + 2), sizeof(char *));
// 	i = 0;
// 	while (com && com[i])
// 	{
// 		new_com[i] = com[i];
// 		i++;
// 	}
// 	new_com[i++] = str;
// 	new_com[i] = NULL;
// 	free(com);
// 	return (new_com);
// }