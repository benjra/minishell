/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:46:52 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/01 11:56:41 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handle_symbol_token(t_token **list, char *str, char *c, int type)
{
	char	*new;

	new = ft_strnstr(str, c, -1); // Locate the symbol
	if (new)
	{
		*new = '\0'; // Terminate the string at the symbol
		if (*(str))
			check_symbols(str, list);                   
				// Process the part before the symbol
		lstadd_backs(list, lstnews(type, ft_strdup(c)));
			// Add the symbol as a token
		new += ft_strlen(c);                             // Move past the symbol
		if (*new)
			check_symbols(new, list); // Process the part after the symbol
	}
}

void	handle_no_symbol_token(t_token **list, char *str, char *c)
{
	int	last;
	int	i;

	last = 0;
	i = 0;
	if (!ft_strncmp(str, c, ft_strlen(c))) // If string starts with the symbol
	{
		while (ft_strnstr(str + last, c, ft_strlen(c)) != NULL)
			last++;
		lstadd_backs(list, lstnews(get_type(str), ft_substr(str, i, last)));
			// Add as token
	}
	else
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
			// Add full string as token
}
// this function add eavh word inside the linked list
void	parse_and_add_token(t_token **list, char *str, char *c, int type)
{
	char	*new;

	new = ft_strchr_skip_quotes(str, c);
	if (new &&ft_strnstr(str, c, ft_strlen(str)) != NULL)
		handle_symbol_token(list, str, c, type);
	else
		handle_no_symbol_token(list, str, c);
}
