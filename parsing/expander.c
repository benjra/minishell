/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/03 20:41:36 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**init_tmp_vars(char *args, char **exp_)
{
	char	**tmp;

	*exp_ = ft_strdup("");
	tmp = (char **)malloc(sizeof(char *) * 3);
	tmp[2] = ft_strdup(args);
	return (tmp);
}

char	*process_word(char *str, char *exp_, t_name *env)
{
	char	*search_tmp;
	char	*tmp_0;
	char	*new_exp_;

	if (ft_strchr(str, '$') && str[0] != '\'')
	{
		search_tmp = search(str, env);
		new_exp_ = ft_strjoin(exp_, search_tmp);
		free(search_tmp);
	}
	else
	{
		tmp_0 = ins_quote(str);
		new_exp_ = ft_strjoin(exp_, tmp_0);
		free(tmp_0);
	}
	free(exp_);
	return (new_exp_);
}

char	*loop_through_string(char *tmp2, char *exp_, t_name *env)
{
	int		j;
	char	*str;
	char	*tmp_0;

	j = 0;
	while (tmp2[j])
	{
		str = get_word(tmp2, &j);
		if (*str == '"')
		{
			tmp_0 = ins_quote(str);
			free(tmp_0);
		}
		exp_ = process_word(str, exp_, env);
		free(str);
		if (!tmp2[j])
			break ;
	}
	return (exp_);
}

char	*small_expand(char *args, t_name *env)
{
	char	**tmp;
	char	*exp_;

	tmp = init_tmp_vars(args, &exp_);
	exp_ = loop_through_string(tmp[2], exp_, env);
	free(args);
	free(tmp[2]);
	free(tmp);
	return (exp_);
}

void	expander(t_lsttoken *tokens, t_name *env)
{
	t_lsttoken	*tmp;
	t_redir		*tm;
	int			i;

	tmp = tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			tmp->args[i] = small_expand(tmp->args[i], env);
			i++;
		}
		tm = tmp->redirections;
		while (tm)
		{
			if (tm->type != TOKEN_REDIR_HEREDOC)
				tm->red = small_expand(tm->red, env);
			else
				tm->red = ins_quote(tm->red);
			tm = tm->next;
		}
		tmp = tmp->next;
	}
}
