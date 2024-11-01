/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:16:51 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:16:52 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	sig_wait(t_lsttoken *token)
{
	int			status;
	t_lsttoken	*current;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	current = token;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			g_var.exit_s = 128 + WTERMSIG(status);
			if (g_var.exit_s == 130)
			{
				write(1, "\n", 1);
			}
			else if (g_var.exit_s == 131)
				write(1, "Quit\n", 6);
		}
		if (WIFEXITED(status))
			g_var.exit_s = WEXITSTATUS(status);
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
