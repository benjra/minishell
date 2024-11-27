/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:32:51 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/27 16:23:19 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	has_quotes(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (1);
		str++;
	}
	return (0);
}

char	*small_expand(char *args, t_name *env)
{
	char	*tmp;
	char	*exp_;

	tmp = init_tmp_vars(args, &exp_);
	exp_ = loop_through_string(tmp, exp_, env);
	free(args);
	free(tmp);
	return (exp_);
}

static void	expand_redirections(t_lsttoken *token, t_name *env)
{
	t_redir	*tm;

	tm = token->redirections;
	while (tm)
	{
		if (tm->type != TOKEN_REDIR_HEREDOC)
			tm->red = small_expand(tm->red, env);
		else
		{
			if (has_quotes(tm->red))
				tm->expand = 0;
			else
				tm->expand = 1;
			tm->red = ins_quote(tm->red);
			token->is_heredoc = 1;
		}
		tm = tm->next;
	}
}

void	expander(t_lsttoken *tokens, t_name *env)
{
	t_lsttoken	*tmp;
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
		expand_redirections(tmp, env);
		tmp = tmp->next;
	}
}
