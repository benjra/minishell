/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:20 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/08/11 20:04:12 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*get_specialcar(char *s)
{
	int	i;

	i = 0;
	while (s[i] &&(( s[i] != ' ' && (ft_isalnum(s[i]))) || s[i]=='_' || s[i]=='?')) // case of - underscore
	{
		i++;
	}
	return (s + i);
}

char	*get_var(int len, char *afterdoll)
{
	char	*var;
	var =ft_strdup("");
	var = ft_substr(afterdoll, 0, len - ft_strlen(get_specialcar(afterdoll)));
	return (var);
}

char	*search_env(int len, char *afterdoll, t_name *env)
{
	char	*replace;
	char	*var;

	var = get_var(len, afterdoll);
	
	replace = ft_env(env, var);
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
	char	*replace;
	char	*expander;

	afterdol = ft_strchr(arg, '$');
	*afterdol= '\0';
	afterdol++;
	ln_befdoll = ft_strlen(arg) - ft_strlen(afterdol);
	ln_aftdoll = ft_strlen(arg) - ln_befdoll;

	replace = search_env(ln_aftdoll, afterdol, env);
	expander=ft_strdup("");
	expander = ft_strjoin(expander, replace);
	return (expander);
}
char *get_word(char *str,int *i) {
    char c = 0;
    char *res = NULL;
    int last = *i;
	
    while (str[last])
	{
		if ((str[last] == '"' && str[last+1]=='"') || (str[last] == '\''  && str[last+1]=='\''))
			last+=2;
		if (str[last] == '"' || str[last] == '\'') 
		{
            c = str[last++]; 
			while (str[last] && (str[last] != c))
	            last++;
			if (str[last])
				last++;
			break;
        }
		else
		{
			if (str[last] == '$' || !ft_isalnum(str[last]))
				last++;
            while (str[last] && (ft_isalnum(str[last]) || str[last] == '_' || str[last] == '?'))
                last++;
            break;
        }
    }
	
	res = ft_strdup(ft_substr(str, *i, last - *i));
	*i = last;
    return res;
}
void	expander(t_lsttoken *tokens, t_name *env)
{
	t_lsttoken	*tmp;
	int			i;
	int j;
	

	tmp = tokens;
	char *exp_ = ft_strdup("");
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			j= 0;
			char *s=ft_strdup(tmp->args[i]);
			while(s[j])
			{
				char *str=get_word(s, &j);//should get the first of args
				if (ft_strchr(str, '$') && str[0] !='\'')
					exp_ = ft_strjoin(exp_, ft_strdup(search(str, env)));
				else
					exp_ = ft_strjoin(exp_, str);
				if (!s[j])
					break;
			}
			tmp->args[i] = exp_;
			exp_ = ft_strdup("");
			i++;
		}
	// free(exp_);
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



