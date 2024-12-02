/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/12/02 21:25:29 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	norm_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	*init_tmp_vars(char *args, char **exp_)
{
	char	*tmp;

	*exp_ = ft_strdup("");
	tmp = ft_strdup(args);
	return (tmp);
}

char	*process_word(char *str, char *exp_, t_name *env)
{
	char	*search_tmp;
	char	*new_exp_;
	char	*ss;

	if (ft_strchr(str, '$'))
	{
		search_tmp = search(ft_strchr(str, '$'), env);
		ss = ft_strchr(str, '$');
		ss = ft_substr(str, 0, ss - str);
		new_exp_ = ft_strjoin(exp_, ss);
		free(ss);
		ss = new_exp_;
		new_exp_ = ft_strjoin(new_exp_, search_tmp);
		free(ss);
		free(search_tmp);
	}
	else
	{
		new_exp_ = ft_strjoin(exp_, str);
	}
	free(str);
	free(exp_);
	return (new_exp_);
}

void	normi_quotes(char *str, char **exp_, t_name *env)
{
	char	*tmp_0;
	int		i;
	char	*tmp2;

	i = 0;
	if (*str == '\'')
	{
		tmp_0 = ins_quote(str);
		free(str);
		str = *exp_;
		*exp_ = ft_strjoin(*exp_, tmp_0);
		norm_free(str, tmp_0);
	}
	else if (ft_strchr1(str, '"') || ft_strchr1(str, '\''))
	{
		tmp2 = ins_quote(str);
		while (tmp2[i])
		{
			tmp_0 = get_word(tmp2, &i);
			*exp_ = process_word(tmp_0, *exp_, env);
		}
		norm_free(str, tmp2);
	}
	else
		*exp_ = process_word(str, *exp_, env);
}

char	*loop_through_string(char *tmp2, char *exp_, t_name *env)
{
	int		j;
	char	*str;

	j = 0;
	if (!tmp2)
		return (ft_strdup(""));
	while (tmp2[j])
	{
		str = get_word(tmp2, &j);
		normi_quotes(str, &exp_, env);
	}
	return (exp_);
}
