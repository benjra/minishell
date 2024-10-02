/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/02 17:09:15 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_specialcar(char *s) // this fun get from a special caracter to end
{
	int i;

	i = 0;
	while (s[i] && ((s[i] != ' ' && (ft_isalnum(s[i]))) || s[i] == '_'
			|| s[i] == '?')) // case of - underscore
	{
		i++;
	}
	return (s + i);
}

char	*get_var(int len, char *afterdoll)
// function foe getting the variable after dollar sign $
{
	char *var;
	// var =ft_strdup("");
	var = ft_substr(afterdoll, 0, len - ft_strlen(get_specialcar(afterdoll)));
	return (var);
}

char	*search_env(int len, char *afterdoll, t_name *env)
// function for retur the value of the variable inside the envierement else empty or 0
{
	char *replace;
	char *var;
	char *tmp;

	var = get_var(len, afterdoll);
	tmp = var;
	replace = ft_env(env, tmp); // get from envirement
	*afterdoll += ft_strlen(tmp);
	free(tmp);
	if (ft_strchr(afterdoll, '$'))
		search_env(ft_strlen(afterdoll), afterdoll, env);
	// recursion if a dollar sign exist in the rest of the string
	return (replace);
}

char	*search(char *arg, t_name *env)
// this function expande the variable from the env
{
	int ln_aftdoll;
	int ln_befdoll;
	char *afterdol;
	char *replace;

	afterdol = ft_strchr(arg, '$');
	*afterdol = '\0';
	afterdol++;
	ln_befdoll = ft_strlen(arg) - ft_strlen(afterdol);
	ln_aftdoll = ft_strlen(arg) - ln_befdoll;

	replace = search_env(ln_aftdoll, afterdol, env);
	return (replace);
}
char	*get_word(char *str, int *i) // this function get every word
{
	char c = 0;
	char *res;
	int last = *i;

	while (str[last])
	{
		if ((str[last] == '\'' && str[last + 1] == '\''))
			last += 2;
		if (str[last] == '\'')
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
				while (str[last] && (ft_isalnum(str[last]) || str[last] == '_'
						|| str[last] == '?'))
					last++;
			}
			break ;
		}
	}
	res = ft_substr(str, *i, last - *i);
	*i = last;
	return (res);
}

// this function is the core of expander it expand a string
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

// the main function of expander it expand exept inside the single quotes but it expand just the arguments of the command
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
