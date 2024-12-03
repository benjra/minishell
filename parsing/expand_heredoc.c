/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:05:12 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/12/02 21:52:02 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
