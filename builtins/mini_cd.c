/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:57:57 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/21 13:58:02 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

int	change_directory(t_name *env, char *path, int flag, int print_path)
{
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];
	char	real_path[PATH_MAX];

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (1);
	if (handle_directory_change(path, real_path) != 0)
	{
		if (flag == 0)
			return (print_cd_error(path, strerror(errno)));
		else
			return (1);
	}
	if (getcwd(newpwd, sizeof(newpwd)) == NULL)
		return (print_cd_error(path, "error retrieving current directory"));
	if (print_path)
		ft_putendl_fd(newpwd, 1);
	return (update_env_vars(env, oldpwd, newpwd));
}

int	handle_cd_dash(t_name *env)
{
	char	*oldpwd;

	oldpwd = get_env_var_value(env, "OLDPWD");
	if (oldpwd == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	return (change_directory(env, oldpwd, 0, 1));
}

int	handle_tilde_expansion(t_name *env, char *arg, char *path)
{
	char	*home;

	home = get_env_var_value(env, "HOME");
	if (home == NULL)
		return (print_cd_error("", "HOME not set"));
	ft_strlcpy(path, home, PATH_MAX);
	ft_strlcat(path, arg + 1, PATH_MAX);
	return (0);
}

int	handle_cd_args(t_name *env, char **argv)
{
	char	path[PATH_MAX];
	int		print_path;

	if (!argv[1] || ft_strcmp(argv[1], "~") == 0)
		return (handle_home_directory(env, get_env_var_value(env, "HOME")));
	if (ft_strcmp(argv[1], "-") == 0)
		return (handle_cd_dash(env));
	if (argv[1][0] == '~')
	{
		if (handle_tilde_expansion(env, argv[1], path) != 0)
			return (1);
		return (try_cdpath(env, path, 0));
	}
	print_path = 0;
	print_path = (get_env_var_value(env, "CDPATH") != NULL);
	return (try_cdpath(env, argv[1], print_path));
}

void	my_cd(t_name *env, char **argv)
{
	g_var.exit_s = 0;
	if (argv[1] && argv[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_var.exit_s = 1;
		return ;
	}
	g_var.exit_s = handle_cd_args(env, argv);
}
