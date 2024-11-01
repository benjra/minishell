/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:16:37 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:16:39 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	print_perror(char *str, int exitt)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	g_var.exit_s = 127;
	if (exitt)
		exit(127);
}

void	my_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		dest[i] = src[i];
	dest[i] = 0;
}

void	check_cmd_path(t_lsttoken *token)
{
	struct stat	statbuf;
	DIR			*dir;

	if (stat(token->args[0], &statbuf) == 0)
	{
		dir = opendir(token->args[0]);
		if (dir == NULL && !access(token->args[0], F_OK)
			&& !access(token->args[0], X_OK))
			token->cmd_path = token->args[0];
		else if (dir != NULL)
		{
			closedir(dir);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(token->args[0], 2);
			ft_putstr_fd(" is a directory\n", 2);
			exit(126);
		}
		else
			print_perror(token->args[0], 1);
	}
	else
		print_perror(token->args[0], 1);
}

int	get_var_index(char *key)
{
	int	j;
	int	i;

	j = -1;
	i = -1;
	while (g_var.envp[++j])
	{
		if (ft_strncmp(g_var.envp[j], key, ft_strlen(key)) == 0)
		{
			i = j;
			break ;
		}
	}
	return (i);
}

void	check_command_name(t_lsttoken *token)
{
	int		i;
	char	**execps_paths;

	i = -1;
	execps_paths = NULL;
	i = get_var_index("PATH=");
	if (i != -1)
	{
		execps_paths = ft_split(g_var.envp[i] + 5, ':');
		token->cmd_path = get_cmd_path(token->args[0], execps_paths);
	}
	else
		check_cmd_path(token);
}
