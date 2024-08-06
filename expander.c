/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/06 11:26:11 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_specialcar(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != ' ' && ft_isalnum(s[i])) // case of - underscore
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

	var = get_var(len, afterdoll);
	replace = ft_env(env, var);
	// printf("---replace: %s---",replace);
	*afterdoll += ft_strlen(var);
	if (ft_strchr(afterdoll, '$'))
		search_env(ft_strlen(afterdoll), afterdoll, env);
	return (replace);
}

char	*search(char *arg, t_name *env)
{
	int		ln_aftdoll;
	int		ln_befdoll;
	char	*afterdol;
	char	*befordoll;
	char	*replace;
	char	*expander;

	afterdol = ft_strchr(arg, '$');
	if (!afterdol)
	{
		printf("No dollar sign found.\n");
		return (NULL);
	}
	*afterdol = '\0';
	afterdol++;
	ln_befdoll = ft_strlen(arg) - ft_strlen(afterdol);
	ln_aftdoll = ft_strlen(arg) - ln_befdoll;
	befordoll = ft_strdup(arg);
	replace = search_env(ln_aftdoll, afterdol, env);
	expander = ft_strjoin(expander, befordoll);
	// having a garbage value before first join
	expander = ft_strjoin(expander, replace);
	expander = ft_strjoin(expander, get_specialcar(afterdol));
	printf("ft_strlen(arg): %lu", ft_strlen(befordoll)
		+ ft_strlen(get_specialcar(afterdol)) + ft_strlen(replace));
	printf("\n<<<<  after $=> %s  >>>>\nBEFORE %s\n<<rep: %s>>\n specia : %s",
		afterdol, befordoll, replace, get_specialcar(afterdol));
	printf("\nexpander: %s\n", expander);
	return (expander);
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
			if (ft_strchr(tmp->args[i], '$'))
			{
				tmp->args[i] = ft_strdup(search(tmp->args[i], env));
			}
			i++;
		}
		tmp = tmp->next;
	}
}
