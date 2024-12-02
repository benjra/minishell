/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:43:13 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/12/02 21:37:29 by bbenjrai         ###   ########.fr       */
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

char	*norm_join(char *afterdoll, char *replace)
{
	char	*tmp;

	tmp = replace;
	replace = ft_strjoin(tmp, afterdoll);
	free(tmp);
	return (replace);
}

char	*search_env(int len, char *afterdoll, t_name *env)
{
	char	*replace;
	char	*var;
	char	*tmp;
	char	*result;
	char	*ss;

	var = get_var(len, afterdoll);
	tmp = var;
	replace = ft_env(env, tmp);
	afterdoll += ft_strlen(var);
	free(var);
	if (ft_strchr(afterdoll, '$'))
	{
		ss = afterdoll;
		afterdoll = ft_strchr(afterdoll, '$');
		afterdoll++;
		ss = ft_substr(ss, 0, afterdoll - ss);
		replace = ft_strjoin(replace, ss);
		result = search_env(ft_strlen(afterdoll), afterdoll, env);
		replace = norm_join(result, replace);
		norm_free(ss, result);
	}
	else if (afterdoll)
		replace = norm_join(afterdoll, replace);
	return (replace);
}

char	*search(char *arg, t_name *env)
{
	int		ln_aftdoll;
	int		ln_befdoll;
	char	*afterdol;
	char	*replace;
	char	*tmp[2];

	afterdol = ft_strchr(arg, '$');
	*afterdol = '\0';
	afterdol++;
	ln_befdoll = ft_strlen(arg) - ft_strlen(afterdol);
	ln_aftdoll = ft_strlen(arg) - ln_befdoll;
	replace = ft_substr(arg, 0, ln_befdoll);
	tmp[0] = replace;
	tmp[1] = search_env(ln_aftdoll, afterdol, env);
	replace = ft_strjoin(tmp[0], tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	return (replace);
}
