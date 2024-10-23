/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:03:18 by assia             #+#    #+#             */
/*   Updated: 2024/10/24 00:27:01 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

void	sync_env_array(t_name *env)
{
	char	**new_env;

	new_env = env_to_array(env);
	if (!new_env)
		return ;
	free_env_array(g_var.envp);
	g_var.envp = new_env;
}

static int	count_env_vars(t_name *env)
{
	int		count;
	t_name	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(t_name *node)
{
	char	*tmp;
	size_t	total_len;

	total_len = ft_strlen(node->name) + ft_strlen(node->value) + 2;
	tmp = malloc(total_len);
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, node->name, total_len);
	ft_strlcat(tmp, "=", total_len);
	ft_strlcat(tmp, node->value, total_len);
	return (tmp);
}

char	**env_to_array(t_name *env)
{
	char	**new_env;
	t_name	*current;
	int		i;

	new_env = (char **)malloc((count_env_vars(env) + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		new_env[i] = create_env_string(current);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			free(new_env);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
