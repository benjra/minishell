/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:06:14 by bbenjrai          #+#    #+#             */
/*   Updated: 2024/10/05 16:29:43 by bbenjrai         ###   ########.fr       */
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

	(void)env;
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
	set_num_cmds(current);
	execute_args(*current, env);
	free_all(current);
}
