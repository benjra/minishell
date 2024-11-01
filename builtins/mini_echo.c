/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:14:10 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:14:12 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	print_cd_error(char *path, char *error_msg)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	handle_directory_change(char *path, char *real_path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir == NULL)
		return (1);
	closedir(dir);
	if (chdir(path) != 0)
		return (1);
	if (getcwd(real_path, PATH_MAX) == NULL)
		return (1);
	return (0);
}

int	is_n_option(char *arg)
{
	int	i;

	if (arg[0] != '-' || arg[1] == '\0')
		return (0);
	i = 1;
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	my_echo(char **av)
{
	int	newline;
	int	arg_start;
	int	i;

	g_var.exit_s = 0;
	newline = 1;
	arg_start = 1;
	while (av[arg_start] && is_n_option(av[arg_start]))
	{
		newline = 0;
		arg_start++;
	}
	i = arg_start;
	while (av[i])
	{
		ft_putstr_fd(av[i], g_var.out_fd);
		if (av[i + 1])
			ft_putstr_fd(" ", g_var.out_fd);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", g_var.out_fd);
}
