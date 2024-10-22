/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/21 14:37:37 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_specialcar(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] != ' ' && (ft_isalnum(s[i]))) || s[i] == '_'
			|| s[i] == '?'))
	{
		i++;
	}
	return (s + i);
}

char	*get_var(int len, char *afterdoll)
{
	char	*var;

	var = ft_substr(afterdoll, 0, len - ft_strlen(get_specialcar(afterdoll)));
	return (var);
}


char	*search_env(int len, char *afterdoll, t_name *env)
{
	char	*replace;
	char	*var;
	char	*tmp;

	var = get_var(len, afterdoll);
	tmp = var;
	replace = ft_env(env, tmp);
	
	afterdoll += ft_strlen(var);
	free(var);
	if (ft_strchr(afterdoll, '$'))
		search_env(ft_strlen(afterdoll), afterdoll, env);
	else if (afterdoll)
	{
		tmp  = replace;
		replace = ft_strjoin(tmp, afterdoll);
		free(tmp);
	}
	return (replace);
}

char	*search(char *arg, t_name *env)
{
	int		ln_aftdoll;
	int		ln_befdoll;
	char	*afterdol;
	char	*replace;

	afterdol = ft_strchr(arg, '$');
	*afterdol = '\0';
	afterdol++;
	ln_befdoll = ft_strlen(arg) - ft_strlen(afterdol);
	ln_aftdoll = ft_strlen(arg) - ln_befdoll;
	replace = ft_substr(arg, 0 , ln_befdoll);
	char * tmp = replace;
	replace = ft_strjoin(replace,search_env(ln_aftdoll, afterdol, env));
	free(tmp);
	return (replace);
}

char	*get_word(char *str, int *i)
{
	char	c;
	char	*res;
	int		last;

	c = 0;
	last = *i;
	if (!str)
		return (ft_strdup(""));
	while (str[last])
	{
		
		if (str[last] == '\'' || str[last] == '\"') 
		{
			c = str[last++];
			while (str[last] && (str[last] != c))
				last++;
			if (str[last])
				last++;
			break ;
		}
		else
		{
			if (str[last])
			{
				if (str[last] == '$' || !ft_isalnum(str[last]))
					last++;
				if(str[last] && str[last]=='?')
				{
						last++;	
						break;
				}
				while (str[last] && (ft_isalnum(str[last]) || str[last] == '_'
						|| str[last] == '?'))
				{
					last++;
				}
			}
			break ;
		}
	}
	res = ft_substr(str, *i, last - *i);
	*i = last;
	return (res);
}

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

	if (ft_strchr(str, '$'))
	{
		search_tmp = search(str, env);
		new_exp_ = ft_strjoin(exp_, search_tmp);
		free(search_tmp);
	}
	else
	{
		tmp_0 = str;
		new_exp_ = ft_strjoin(exp_, str);
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
		if (*str == '\'')
		{
			tmp_0 = ins_quote(str);
			exp_ = ft_strjoin(exp_, tmp_0);
			free(tmp_0);
		}
		else if  (*str == '"')
		{
			tmp_0 = ins_quote(str);
			exp_ = process_word(tmp_0, exp_, env);
		}
		else
			exp_ = process_word(str, exp_, env);
		// free(str);
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
			{
				tm->red = ins_quote(tm->red);
				tmp->is_heredoc = 1;
			}
			tm = tm->next;
		}
		tmp = tmp->next;
	}
}
