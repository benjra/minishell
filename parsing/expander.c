/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/09/29 16:54:51 by bbenjrai         ###   ########.fr       */
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
		//(str[last] == '"' && str[last+1]=='"') || str[last] == '"' ||
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
	// printf("{%s}\n", res);
	return (res);
}
char	*small_expand(char *args, t_name *env)
// this function is the core of expander it expand a string
{
	int j;
	char *tmp;
	char *tmp2;
	char *search_tmp;
	char *exp_ = ft_strdup("");
	char *s = ft_strdup(args);
	j = 0;
	while (s[j])
	{
		char *str = get_word(s, &j);
		if (*str == '"')
		{
			tmp2 = ins_quote(str);
			// this function remove quotes if u want use it or not when u expand
			free(tmp2);
		}
		tmp = exp_;
		if (ft_strchr(str, '$') && str[0] != '\'')
		{
			search_tmp = search(str, env);
			exp_ = ft_strjoin(exp_, search_tmp);
			free(search_tmp);//i have here double free 
		}
		else
		{
			tmp2 = ins_quote(str);
			exp_ = ft_strjoin(exp_, tmp2);
			free(tmp2);
		}
		free(tmp);
		free(str);
		if (!s[j])
			break ;
	}
	free(args);
	free(s);
	return (exp_);
}
void	expander(t_lsttoken *tokens, t_name *env)
// the main function of expander it expand exept inside the single quotes but it expand just the arguments of the command
{
	t_lsttoken *tmp;
	t_redir *tm;
	int i;

	tmp = tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			// inside this while can be a function separated
			tmp->args[i] = small_expand(tmp->args[i], env);
			// this function u can use it to expand any string not just the args
			i++;
		}
		///
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
