/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:37:25 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/20 20:43:55 by bbenjrai         ###   ########.fr       */
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
	// if (*afterdoll != '\'' && *afterdoll != '"')
	// 	*tmp = 14;
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
	printf("afterdoll 2= %s\n",afterdoll);//problem not here
	return (replace);
}

char	*search(char *arg, t_name *env)
{
	int		ln_aftdoll;
	int		ln_befdoll;
	char	*afterdol;
	char	*replace;

	afterdol = ft_strchr(arg, '$');
	printf("afterdoll = %s\n",afterdol);
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
