/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:24:30 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/12/04 20:27:40 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_name	*tail(t_name *list)
{
	t_name	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	lstadd_back(t_name **lst, t_name *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		tail(*lst)->next = new;
}

t_name	*lstnew(char *name, char *value)
{
	t_name	*linked_lst;

	linked_lst = malloc(sizeof(t_name));
	if (!linked_lst)
		return (NULL);
	if (name)
		linked_lst->name = ft_strdup(name);
	else
		linked_lst->name = NULL;
	if (value)
		linked_lst->value = ft_strdup(value);
	else
		linked_lst->value = NULL;
	linked_lst->next = NULL;
	return (linked_lst);
}

t_name	*fill_env(char **env)
{
	char	*name;
	char	*value;
	char	*en;
	int		i;
	t_name	*lst;
	char	pwd[4096];

	lst = NULL;
	if (!env)
	{
		if (getcwd(pwd, sizeof(pwd)))
		{
			g_var.envp = malloc(sizeof(char *) * 4);
			if (!g_var.envp)
				return (NULL);
			lstadd_back(&lst, lstnew("PWD", pwd));
			g_var.envp[0] = ft_strjoin("PWD=", pwd);
			g_var.envp[1] = ft_strdup("SHLVL=1");
			g_var.envp[2] = ft_strdup("OLDPWD");
			g_var.envp[3] = NULL;
			lstadd_back(&lst, lstnew("SHLVL", "1"));
			lstadd_back(&lst, lstnew("OLDPWD", NULL));
		}
		return (lst);
	}
	i = 0;
	while (env && env[i])
	{
		en = ft_strdup(env[i]);
		value = ft_strchr(en, '=');
		*value = 0;
		value++;
		name = en;
		lstadd_back(&lst, lstnew(name, value));
		i++;
		free(en);
	}
	return (lst);
}
