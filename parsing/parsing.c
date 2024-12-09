/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:35:52 by amabchou          #+#    #+#             */
/*   Updated: 2024/12/08 19:47:05 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	count_total_cmds(t_lsttoken *head)
{
	int			tot_cmds;
	t_lsttoken	*current;

	tot_cmds = 0;
	current = head;
	while (current != NULL)
	{
		tot_cmds++;
		current = current->next;
	}
	g_var.size = tot_cmds;
}

void	alistclear(t_alst **lista)
{
	t_alst	*tmp;

	while (*lista)
	{
		tmp = (*lista)->next;
		if (*lista && (*lista)->content)
			free((*lista)->content);
		if (*lista)
			free(*lista);
		(*lista) = tmp;
	}
}

void	setup_parsing(t_name *env, t_lsttoken *current)
{
	init_g_var(&current);
	count_total_cmds(current);
	execute_args(current, env);
	alistclear(g_var.alist);
	free(g_var.alist);
	ft_malloc(0, -1);
	free_all(current);
	free(g_var.fd);
}

void	parsing(char *str, t_name *env)
{
	char		**string;
	t_token		*list;
	t_lsttoken	*list2;

	g_var.alist = malloc(sizeof(t_alst *));
	*(g_var.alist) = NULL;
	string = split_string(str);
	list = fill_list(string);
	free_arg(string);
	if (printf_err(list))
	{
		freelist1(list);
		free(g_var.alist);
		return ;
	}
	list2 = fill_token(list);
	freelist1(list);
	expander(list2, env);
	setup_parsing(env, list2);
}
