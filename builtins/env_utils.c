/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:13:13 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/01 17:13:15 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

static char	*create_env_string_with_value(t_name *env_node)
{
	char	*env_str;
	size_t	len;

	len = ft_strlen(env_node->name) + 1;
	if (env_node->value)
		len += ft_strlen(env_node->value);
	env_str = (char *)malloc(len + 1);
	if (!env_str)
		return (NULL);
	ft_strlcpy(env_str, env_node->name, len + 1);
	ft_strlcat(env_str, "=", len + 1);
	if (env_node->value)
		ft_strlcat(env_str, env_node->value, len + 1);
	return (env_str);
}

char	*create_env_string(t_name *env_node)
{
	if (!env_node || !env_node->name)
		return (NULL);
	if (env_node->value == NULL)
		return (ft_strdup(env_node->name));
	return (create_env_string_with_value(env_node));
}

static int	count_valid_env_entries(t_name *env)
{
	int		count;
	t_name	*current;

	count = 0;
	current = env;
	while (current)
	{
		if (current->value != NULL)
			count++;
		current = current->next;
	}
	return (count);
}

static int	populate_env_array(char **env_array, t_name *env, int count)
{
	int		i;
	t_name	*current;

	i = 0;
	current = env;
	while (current && i < count)
	{
		if (current->value != NULL)
		{
			env_array[i] = create_env_string(current);
			if (!env_array[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	env_array[i] = NULL;
	return (1);
}

char	**env_to_array(t_name *env)
{
	int		count;
	char	**env_array;
	int		i;

	count = count_valid_env_entries(env);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	if (!populate_env_array(env_array, env, count))
	{
		i = 0;
		while (env_array[i])
			free(env_array[i++]);
		free(env_array);
		return (NULL);
	}
	return (env_array);
}
