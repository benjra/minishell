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

t_name  *copy_env(t_name *env)
{
    t_name *new_env;
    t_name *current;
    t_name *last_node;
    t_name  *new_node;

    new_env = NULL;
    current = env;
    last_node = NULL;
    while (current)
    {
        new_node = create_new_node(current->name, current->value);
        if (!new_node)
        {
            free_env(new_env);
            return NULL;
        }
        if (!new_env)
            new_env = new_node;
        else
            last_node->next = new_node;
        last_node = new_node;
        current = current->next;
    }
    return new_env;
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

void update_node(t_name *node, const char *value)
{
    free(node->value);
    if (value)
        node->value = ft_strdup(value);
    else
        node->value = ft_strdup("");
    if (!node->value)
        perror("malloc");
}
