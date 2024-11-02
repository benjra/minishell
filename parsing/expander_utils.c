/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/26 16:20:58 by bbenjrai         ###   ########.fr       */
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

	if (ft_strchr(str, '$'))
	{
		search_tmp = search(str, env);
		new_exp_ = ft_strjoin(exp_, search_tmp);
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

	if (g_var.flag==1 &&  *str == '\'')
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
			g_var.flag=0;
			tmp_0 = ins_quote(str);
		*exp_=loop_through_string(tmp_0,*exp_,env);
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
		if (!tmp2[j])
			break ;
	}
	return (exp_);
}
