/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:06:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/13 13:13:09 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count] != NULL)
	{
		count++;
	}
	return (count);
}

void	set_num_cmds(t_lsttoken *lsttoken)
{
	if (lsttoken && lsttoken->args)
	{
		lsttoken->num_cmds = count_args(lsttoken->args);
	}
}

void	parsing(char *str, t_name *env)
{
	char		**string;
	t_token		*list;
	t_lsttoken	*list2;
	t_lsttoken	*current;

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
	int i;
	current = list2;
	while (current) 
{
	
	i = 0;
	while (current->args != NULL && current->args[i] != NULL)
	{
		printf("%d",i);
	    printf("args : ----%s  \n", current->args[i++]);
	}
	while (current->redirections != NULL)
	{
	    printf("red : -- %s \n", current->redirections->red);
		current->redirections = current->redirections->next;
	}
	    current = current->next; 
	
	// free_all(current);
	}
 
	set_num_cmds(current);
	execute_args(*current, env);
	free_all(current);
}
