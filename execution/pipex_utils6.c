/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:16:43 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:16:45 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

char	*add_something(char *str, char *add)
{
	return (ft_strjoin(str, add));
}

int	validate_var_name(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (!(ft_isalpha(var[i]) || (ft_isdigit(var[i]) && i != 0)
				|| var[i] == '_'))
			break ;
	}
	return (i);
}

char	*my_dup(const char *s)
{
	void	*res;
	size_t	i;
	size_t	l;
	char	*fif;

	l = ft_strlen(s);
	res = malloc(l + 1);
	if (!res)
	{
		perror("");
		exit(errno);
	}
	lista_add_front(g_var.alist, lista_new(res));
	fif = res;
	if (!fif)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		fif[i] = s[i];
		i++;
	}
	fif[i] = '\0';
	return (fif);
}

char	*until_dollar(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (str[i] == '$')
		return (my_dup("$"));
	while (str[i])
	{
		if (!flag && (str[i] == '\'' || str[i] == '\"'))
			flag = str[i];
		else if (flag && str[i] == flag)
			flag = 0;
		if (str[i] == '$' && flag != '\'')
			break ;
		i++;
	}
	return (ft_substr(str, 0, i));
}

char	*exit_status(char *variable, int *i)
{
	char	*output;

	output = "";
	output = ft_strjoin(output, variable);
	(*i) += 2;
	return (output);
}
