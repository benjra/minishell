#include "../parsing/mini.h"

void	swap_nodes(t_name *a, t_name *b)
{
    char	*temp_name;
    char	*temp_value;

    temp_name = a->name;
    temp_value = a->value;
    a->name = b->name;
    a->value = b->value;
    b->name = temp_name;
    b->value = temp_value;
}

t_name	*bubble_sort_env(t_name *env)
{
    int		swapped;
    t_name	*ptr1;
    t_name	*lptr;

    if (!env)
        return (NULL);
    lptr = NULL;
    while (1)
    {
        swapped = 0;
        ptr1 = env;
        while (ptr1->next != lptr)
        {
            if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
            {
                swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
        if (!swapped)
            break ;
    }
    return (env);
}

t_name	*copy_env(t_name *env)
{
    t_name	*new_env;
    t_name	*current;
    t_name	*new_node;
    t_name	*last_node;

    if (!env)
        return (NULL);
    new_env = NULL;
    current = env;
    last_node = NULL;
    while (current)
    {
        new_node = (t_name *)malloc(sizeof(t_name));
        if (!new_node)
        {
            perror("malloc");
            while (new_env)
            {
                t_name *temp = new_env;
                new_env = new_env->next;
                free(temp->name);
                free(temp->value);
                free(temp);
            }
            return (NULL);
        }
        new_node->name = ft_strdup(current->name);
        if (current->value)
            new_node->value = ft_strdup(current->value);
        else
            new_node->value = NULL;
        new_node->next = NULL;
        if (!new_env)
            new_env = new_node;
        else
            last_node->next = new_node;
        last_node = new_node;
        current = current->next;
    }
    return (new_env);
}

void	print_export(t_name *env)
{
    t_name	*current;

    current = bubble_sort_env(env);
    while (current)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(current->name, 1);
        if (current->value)
        {
            ft_putstr_fd("=\"", 1);
            ft_putstr_fd(current->value, 1);
            ft_putstr_fd("\"", 1);
        }
        ft_putstr_fd("\n", 1);
        current = current->next;
    }
}

void	update_or_add_env(t_name **env, const char *var, const char *value)
{
    t_name	*current;
    t_name	*prev;
    t_name	*new_node;

    current = *env;
    prev = NULL;
    while (current)
    {
        if (ft_strcmp(current->name, var) == 0)
        {
            free(current->value);
            if (value)
                current->value = ft_strdup(value);
            else
                current->value = NULL;
            return ;
        }
        prev = current;
        current = current->next;
    }
    new_node = (t_name *)malloc(sizeof(t_name));
    if (!new_node)
    {
        perror("malloc");
        return ;
    }
    new_node->name = ft_strdup(var);
    if (value)
        new_node->value = ft_strdup(value);
    else
        new_node->value = NULL;
    new_node->next = NULL;
    if (prev)
        prev->next = new_node;
    else
        *env = new_node;
}

void	my_export(t_name *env, char **cmd)
{
    t_name	*env_copy;
    int		i;
    char	*eq_pos;
    char	*var;
    char	*value;

    if (cmd[1] == NULL)
    {
        env_copy = copy_env(env);
        if (!env_copy)
        {
            ft_putstr_fd("Failed to copy environment\n", 2);
            return ;
        }
        print_export(env_copy);
        while (env_copy)
        {
            t_name *temp = env_copy;
            env_copy = env_copy->next;
            free(temp->name);
            free(temp->value);
            free(temp);
        }
        return ;
    }
    i = 1;
    while (cmd[i])
    {
        eq_pos = ft_strchr(cmd[i], '=');
        if (eq_pos)
        {
            *eq_pos = '\0';
            var = cmd[i];
            value = eq_pos + 1;
        }
        else
        {
            var = cmd[i];
            value = NULL;
        }
        if (!is_valid_variable(var))
        {
            ft_putstr_fd("export: invalid variable name '", 2);
            ft_putstr_fd(var, 2);
            ft_putstr_fd("'\n", 2);
            i++;
            continue ;
        }
        update_or_add_env(&env, var, value);
        i++;
    }
}