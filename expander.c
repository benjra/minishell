/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/07 21:27:11 by bbenjrai         ###   ########.fr       */
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
	// free(var);
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
	*afterdol= '\0';
	afterdol++;
	ln_befdoll = ft_strlen(arg) - ft_strlen(afterdol);
	ln_aftdoll = ft_strlen(arg) - ln_befdoll;
	befordoll = ft_strdup(arg);
	replace = search_env(ln_aftdoll, afterdol, env);
	expander=ft_strdup("");
	expander = ft_strjoin(expander, befordoll);
	expander = ft_strjoin(expander, replace);
	expander = ft_strjoin(expander, get_specialcar(afterdol));
	printf("ft_strlen(arg): %lu", ft_strlen(befordoll)
		+ ft_strlen(get_specialcar(afterdol)) + ft_strlen(replace));
	printf("\n<<<<  after $=> %s  >>>>\nBEFORE %s\n<<rep: %s>>\n specia : %s",
		afterdol, befordoll, replace, get_specialcar(afterdol));
	printf("\nexpander: %s\n", expander);
	return (expander);
}

char *get_word(char *str)
{
	int i;
	char c=0;
	char *res;
	int first;
	
	first=0;
	i=first;
	while(str[i])
	{
		if(str[i]=='$' || str[i]=='"' || str[i]=='\'')
		{
			if(str[i]=='$')
				i++;
			else if( str[i]=='"' || str[i]=='\'')
				c=str[i++];
		}
		while(str[i] && c!=str[i])
			i++;
		i++;
	}
	res=ft_strdup(ft_substr(str,first,i));
	return res;
}
void	expander(t_lsttoken *tokens, t_name *env)
{
	t_lsttoken	*tmp;
	int			i;
	int j;
	

	tmp = tokens;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			char *str=get_word(tmp->args[i]);//should get the first of args
			while(str[j])
				{
					if (ft_strchr(str, '$') && str[j]!='\'')
					{
						tmp->args[i] = ft_strdup(search(tmp->args[i], env));
					}
				}
			i++;
		}
		tmp = tmp->next;
	}
}















// void	expander(t_lsttoken *tokens, t_name *env)
// {
// 	t_lsttoken	*tmp;
// 	int			i;
// 	char c;
// 	char close='n';
// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->args[i])
// 		{
// 			char *str=tmp->args[i];
// 			if (ft_strchr(tmp->args[i], '$'))
// 			{
// 				int j = 0;
// 				while (str[j])
// 				{
// 					if (str[j] == '"' || str[j] == '\'')
// 					{
// 						c = str[j++];
// 						while (str[j] && c != str[j])
// 						{
// 							if ((c == '"' && str[j] == '"') || (c == '\'' && str[j] == '\''))
// 							{
// 								close=str[i];
// 							}
// 							if (ft_strchr(str, '$') && c == '"' && str[i+1]=='\0' && close=='"')
// 								tmp->args[i] = ft_strdup(search(tmp->args[i], env));
// 							else if (ft_strchr(str, '$') && c == '\'' && close!='n')
// 								return; //should handle this case 
// 							else
// 								tmp->args[i] = ft_strdup(search(tmp->args[i], env));
// 						}
// 					}
// 					j++;
// 				}
// 			}
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// }



