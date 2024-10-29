/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:00:58 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/26 00:45:37 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	sig_wait(t_lsttoken *token)
{
	int			i;
	t_lsttoken	*current;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	i = -1;
	current = token;
	while (current && (g_var.size > 1 || check_builtin(token) == -1))
	{
		if (++i == 0)
		{
			waitpid(g_var.last_child_id, &g_var.exit_s, 0);
			if (WIFEXITED(g_var.exit_s))
				g_var.exit_s = WEXITSTATUS(g_var.exit_s);
			else if (g_var.exit_s == 3 || g_var.exit_s == 2)
				g_var.exit_s += 128;
		}
		else
		{
			waitpid(-1, NULL, 0);
		}
		current = current->next;
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*just_copy(char *target, int *i)
{
	char	*output;
	char	*variable;

	output = "";
	variable = until_dollar(&target[(*i)]);
	output = ft_strjoin(output, variable);
	(*i) += ft_strlen(variable);
	return (output);
}

char	*digit(char *target, int *i)
{
	char	*output;
	char	*variable;

	output = "";
	if (target[(*i) + 1] == '0')
	{
		output = ft_strjoin(output, "Minishell");
		(*i) += ft_strlen(until_dollar(&target[(*i)])) + 1;
	}
	else
	{
		variable = until_dollar(&target[(*i) + 2]);
		output = ft_strjoin(output, variable);
		(*i) += ft_strlen(variable) + 2;
	}
	return (output);
}

char	*gotta_expand(char *target, int flag, int *i)
{
	int		idx;
	char	*output;
	char	*variable;

	output = 0;
	variable = ft_substr(&target[(*i)] + 1, 0, validate_var_name(&target[(*i)]
				+ 1));
	idx = get_var_index(add_something(variable, "="));
	if (idx != -1)
	{
		output = ft_strjoin(output, get_var_val(idx));
		(*i) += validate_var_name(&target[(*i)] + 1) + 1;
	}
	else if (flag == 1)
	{
		output = ft_strjoin(output, add_something("$", variable));
		(*i) += validate_var_name(&target[(*i)] + 1) + 1;
	}
	else
	{
		variable = until_dollar(&target[(*i) + 1]);
		output = ft_strjoin(output, "");
		(*i) += validate_var_name(&target[(*i)] + 1) + 1;
	}
	return (output);
}

char	*get_var_val(int var_index)
{
	char	*val;
	char	*var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	val = NULL;
	var = g_var.envp[var_index];
	while (var[i] && var[i] != '=')
		i++;
	if (var[i])
	{
		while (var[i + j])
			j++;
		val = malloc(j + 1);
		if (!val)
		{
			perror("");
			exit(errno);
		}
		lista_add_front(g_var.alist, lista_new(val));
		my_strncpy(val, var + i + 1, j);
	}
	return (val);
}
