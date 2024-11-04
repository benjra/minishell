/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:43:13 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/11/01 18:08:39 by amabchou         ###   ########.fr       */
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

void	normi(char **replace, char *tmp, char *afterdoll)
{
	tmp = *replace;
	*replace = ft_strjoin(tmp, afterdoll);
	free(tmp);
}

char	*search_env(int len, char *afterdoll, t_name *env)
{
	char	*replace;
	char	*var;
	char	*tmp;
	char	*result;

	if (*afterdoll == '$')
		afterdoll++;
	var = get_var(len, afterdoll);
	tmp = var;
	replace = ft_env(env, tmp);
	afterdoll += ft_strlen(var);
	free(var);
	if (ft_strchr(afterdoll, '$'))
	{
		result = search_env(ft_strlen(afterdoll), afterdoll, env);
		tmp = replace;
		replace = ft_strjoin(tmp, result);
		free(tmp);
		free(result);
	}
	else if (afterdoll)
		normi(&replace, tmp, afterdoll);
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
	afterdol++;
	ln_befdoll = ft_strlen(arg) - ft_strlen(afterdol) - 1;
	ln_aftdoll = ft_strlen(arg) - ln_befdoll;
	if (*arg == '\'')
		ln_aftdoll = ft_strlen(arg) - ln_befdoll - 1;
	else
		ln_aftdoll = ft_strlen(arg) - ln_befdoll;
	replace = ft_substr(arg, 0, ln_befdoll);
	tmp[0] = replace;
	tmp[1] = search_env(ln_aftdoll, afterdol, env);
	replace = ft_strjoin(tmp[0], tmp[1]);
	free(tmp[0]);
	free(tmp[1]);
	return (replace);
}
