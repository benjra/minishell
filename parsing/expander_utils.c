/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/16 12:40:32 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
		ss = ft_substr(str , 0 , ss - str );
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

	if (*str == '\'')
	{
		tmp_0 = ins_quote(str);
		free(str);
		str = *exp_;
		*exp_ = ft_strjoin(*exp_, tmp_0);
		free(str);
		free(tmp_0);
	}
	else if (*str == '"')
	{
		tmp_0 = ins_quote(str);
		*exp_ = process_word(tmp_0, *exp_, env);
		free(str);
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

char	*loop_through_string__(char *tmp2, char *exp_, t_name *env)
{
	int		j;
	char	*str;

	j = 0;
	
	if (!tmp2)
		return (ft_strdup(""));
	while (tmp2[j])
	{
		str = get_word__(tmp2, &j);
		exp_ = process_word(str, exp_, env);
	}
	return (exp_);
}

char	*small_expand__(char *args, t_name *env)
{
	char	*tmp;
	char	*exp_;

	tmp = init_tmp_vars(args, &exp_);
	exp_ = loop_through_string__(tmp, exp_, env);
	free(args);
	free(tmp);
	return (exp_);
}