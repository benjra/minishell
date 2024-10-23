/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assia <assia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 00:03:18 by assia             #+#    #+#             */
/*   Updated: 2024/10/24 00:03:39 by assia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/mini.h"

void    free_env_array(char **env_array)
{
    int i;

    if (!env_array)
        return;
    i = 0;
    while (env_array[i])
    {
        free(env_array[i]);
        i++;
    }
    free(env_array);
}

char	**env_to_array(t_name *env)
{
    int count = 0;
    t_name *current = env;
    char **new_env;
    char *tmp;
    int i = 0;

    while (current)
    {
        count++;
        current = current->next;
    }
    new_env = (char **)malloc((count + 1) * sizeof(char *));
    if (!new_env)
        return (NULL);
    current = env;
    while (current)
    {
        tmp = malloc(ft_strlen(current->name) + ft_strlen(current->value) + 2);
        if (!tmp)
        {
            while (--i >= 0)
                free(new_env[i]);
            free(new_env);
            return (NULL);
        }        
        ft_strlcpy(tmp, current->name, ft_strlen(current->name) + 1);
        ft_strlcat(tmp, "=", ft_strlen(current->name) + 2);
        ft_strlcat(tmp, current->value, ft_strlen(current->name) + ft_strlen(current->value) + 2);
        new_env[i++] = tmp;
        current = current->next;
    }
    new_env[i] = NULL;
    return (new_env);
}

void    sync_env_array(t_name *env)
{
    char    **new_env;

    new_env = env_to_array(env);
    if (!new_env)
        return;    
    free_env_array(g_var.envp);
    g_var.envp = new_env;
}
