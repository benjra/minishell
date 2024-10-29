/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:57:48 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/29 11:20:43 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	update_env_vars(t_name *env, const char *oldpwd, const char *newpwd)
{
	update_or_add_env(&env, "OLDPWD", oldpwd, 1);
	update_or_add_env(&env, "PWD", newpwd, 1);
	sync_env_array(env);
	return (0);
}

char	*get_env_var_value(t_name *env, const char *var)
{
	t_name	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->name, var) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	try_cdpath(t_name *env, char *path, int print_path)
{
	char	*cdpath;
	char	try_path[PATH_MAX];
	char	**cdpath_dirs;
	int		i;

	cdpath = get_env_var_value(env, "CDPATH");
	if (!cdpath || path[0] == '/' || ft_strncmp(path, "./", 2) == 0
		|| ft_strncmp(path, "../", 3) == 0)
		return (change_directory(env, path, 0, 0));
	cdpath_dirs = ft_split(cdpath, ':');
	i = 0;
	while (cdpath_dirs[i])
	{
		ft_strlcpy(try_path, cdpath_dirs[i], sizeof(try_path));
		ft_strlcat(try_path, "/", sizeof(try_path));
		ft_strlcat(try_path, path, sizeof(try_path));
		if (change_directory(env, try_path, 1, print_path) == 0)
		{
			free_split(cdpath_dirs);
			return (0);
		}
		i++;
	}
	free_split(cdpath_dirs);
	return (change_directory(env, path, 0, 0));
}

int	handle_home_directory(t_name *env, char *home)
{
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	return (change_directory(env, home, 0, 0));
}
