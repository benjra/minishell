/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:06:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/22 08:12:06 by bbenjrai         ###   ########.fr       */
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
void	parsing(char *str, t_name *env)
{
	char		**string;
	t_token		*list;
	t_lsttoken	*list2;
	t_lsttoken	*current;

	g_var.alist = malloc(sizeof(t_alst *));
	*(g_var.alist) = NULL;
	string = split_string(str);
	list = fill_list(string);
	free_arg(string);
	
	if (printf_err(list))
	{
		freelist1(list);
		return ;
	}
	list2 = fill_token(list);
	freelist1(list);
	expander(list2, env);
	// if (ft_ambigious(list2)) should handled in execution 
	// {
	// 	ex = 1;
	// 	ft_putendl_fd("ambiguous redirect", 2);
	// 	return ;
	// }
	current = list2;

// int i;
// 	while (current) 
// {
	
// 	i = 0;
// 	while (current->args != NULL && current->args[i] != NULL)
// 	{
// 		printf("%d",i);
// 	    printf("args : ----%s  \n", current->args[i++]);
// 	}
// 	while (current->redirections != NULL)
// 	{
// 	    printf("red : -- %s \n", current->redirections->red);
// 		current->redirections = current->redirections->next;
// 	}
// 	    current = current->next; 
	
// 	free_all(current);
// 	}

	init_g_var(&current);
	count_total_cmds(current);
	execute_args(current, env);
	alistclear(g_var.alist);
	free_all(current);
}
