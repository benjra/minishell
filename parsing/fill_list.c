/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:25 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/03 18:59:57 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	get_type(char *lst)
{
	if (ft_strncmp(lst, ">", 1) == 0 || ft_strncmp(lst, "<", 1) == 0
		|| ft_strncmp(lst, "|", 1) == 0 || ft_strncmp(lst, "<<", 2) == 0
		|| ft_strncmp(lst, ">>", 2) == 0)
	{
		if (ft_strncmp(lst, "|", 1) == 0)
			return (2);
		else if (ft_strncmp(lst, "<<", 2) == 0)
			return (6);
		else if (ft_strncmp(lst, ">>", 2) == 0)
			return (5);
		if (ft_strncmp(lst, ">", 1) == 0)
			return (4);
		else if (ft_strncmp(lst, "<", 1) == 0)
			return (5);
	}
	return (1);
}

t_token	*tails(t_token *list)
{
	t_token	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	lstadd_backs(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		tails(*lst)->next = new;
}

t_token	*lstnews(int type, char *value)
{
	t_token	*linked_lst;

	linked_lst = malloc(sizeof(t_token));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
	linked_lst->type = type;
	linked_lst->value = value;
	linked_lst->next = NULL;
	return (linked_lst);
}

void	check_symbols(char *str, t_token **list)
{
	if (ft_strnstr(str, ">>", -1) && ft_strncmp(str, ">>", -1))
		parse_and_add_token(list, str, ">>", 5);
	else if (ft_strnstr(str, "<<", -1) && ft_strncmp(str, "<<", -1))
		parse_and_add_token(list, str, "<<", 6);
	else if (ft_strchr(str, '|') && ft_strncmp(str, "|", -1))
		parse_and_add_token(list, str, "|", 2);
	else if (ft_strchr(str, '<') && ft_strncmp(str, "<", -1) && ft_strncmp(str,
			"<<", -1))
		parse_and_add_token(list, str, "<", 3);
	else if (ft_strchr(str, '>') && ft_strncmp(str, ">", -1) && ft_strncmp(str,
			">>", -1))
		parse_and_add_token(list, str, ">", 4);
	else
		lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
}

char	*ft_strchr_skip_quotes(const char *str, char *c)
{
	char	in_quotes;

	in_quotes = 0;
	int i=0;
	int end=0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			in_quotes = *str;
			while(*str++ && *str!=in_quotes)
			{
				str++;
				end++;
				if(*str==in_quotes)
				{
					in_quotes=0;
					return(ft_substr(str,i,end));
				}
			}
		}
		else if (ft_strncmp(str, c, ft_strlen(c)) && *str!=in_quotes )
		{ // to avoid the cases like when u want to search for an string
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}



void	parse_and_add_token(t_token **list, char *str, char *c, int type)//this function add eavh word inside the linked list 
{
	char	*new;
	int i=0;
	int last=0;
	(void)type;
//should change this function to being adaptate with cases like ls>cat
	new = ft_strchr_skip_quotes(str, c);//skipp symbols inside quotes
	if (new && ft_strnstr(str,c,ft_strlen(str))!=NULL)
	{
		new=ft_strnstr(str,c,-1);
		*new = '\0';
		if (*(str))
		{
			check_symbols(str, list);
		}
		lstadd_backs(list, lstnews(type, ft_strdup(c)));
		new += ft_strlen(c);
		if (*new)
		{
			check_symbols(new, list);
		}
	}
	else if (!new)
	{
		if(!ft_strncmp(str,c,ft_strlen(c)))// i want if just a normal word add it all not char by char 
		{
			while(ft_strnstr(str+last,c,ft_strlen(c))!=NULL)
			{
				last++;
			}
			lstadd_backs(list, lstnews(get_type(str), ft_substr(str,i,last)));
		}
		else 
			lstadd_backs(list, lstnews(get_type(str), ft_strdup(str)));
	}
}


t_token	*fill_list(char **lst)//filling the list every word and its type 
{
	int		i;
	t_token	*list;

	i = 0;
	list = NULL;
	while (lst[i])
	{
		if (ft_strchr(lst[i], '|') || ft_strchr(lst[i], '<')
			|| ft_strchr(lst[i], '>'))
		{
			if (ft_strnstr(lst[i], ">>", -1) && ft_strncmp(lst[i], ">>", -1))
				parse_and_add_token(&list, lst[i], ">>", TOKEN_REDIR_APPEND); // 5
			else if (ft_strnstr(lst[i], "<<", -1) && ft_strncmp(lst[i], "<<",
					-1))
				parse_and_add_token(&list, lst[i], "<<", TOKEN_REDIR_HEREDOC);
			else if (ft_strchr(lst[i], '|') && ft_strncmp(lst[i], "|", -1))
				parse_and_add_token(&list, lst[i], "|", TOKEN_PIPE);
			else if (ft_strchr(lst[i], '<') && ft_strncmp(lst[i], "<", -1)
				&& ft_strncmp(lst[i], "<<", -1))
				parse_and_add_token(&list, lst[i], "<", TOKEN_REDIR_IN);
			else if (ft_strchr(lst[i], '>') && ft_strncmp(lst[i], ">", -1)
				&& ft_strncmp(lst[i], ">>", -1))
				parse_and_add_token(&list, lst[i], ">", TOKEN_REDIR_OUT);
			else
				lstadd_backs(&list, lstnews(get_type(lst[i]),
											ft_strdup(lst[i])));
		}
		else
		{
			lstadd_backs(&list, lstnews(1, ft_strdup(lst[i])));
		}
		i++;
	}
	return (list);
}

// char *get_quoted_word(char *str)
// {
// 	int i = 0;
// 	int quote = 0;
// 	if (str[i++] == '\'' || str[i] == '"')
// 		quote = str[i];
// 	while(str && str[i] && str[i] != quote)
// 		i++;
// 	if (str[i] == quote)
// 		i++;
// 	return (ft_substr(str, 0, i));
// }

// char *get_token(char *str,int i)
// {
// 	// int i = 0;
// 	int specila = 0;
// 	if (str[i] && ft_strchr("'\"<|>", str[i]))
// 	{
// 		specila = str[i];
// 		while(str && str[i] == specila)
// 			i++;
// 		return (ft_substr(str, 0, i));
// 	}
// 	while(str && str[i])
// 	{
// 		if (ft_strchr("'\"<|>", str[i]))
// 			break;
// 		i++;
// 	}
// 	return (ft_substr(str, 0, i));
// }

// void parse_token(t_token **list, char *str)
// {
// 	int i = -1;
// 	while(str && str[++i])
// 	{
// 		t_token *tok = NULL;
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			tok = lstnews(1, get_quoted_word(&str[i]));
// 			lstadd_backs(list, tok);
// 		}
// 		else
// 		{
// 			tok = lstnews(1, get_token(&str[i],i));
// 			lstadd_backs(list, tok);
// 		}
// 	}
// }