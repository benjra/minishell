#include "../parsing/mini.h"

t_name  *create_new_node(const char *var, const char *value)
{
    t_name *new_node;

    new_node = (t_name *)malloc(sizeof(t_name));
    if (!new_node)
    {
        perror("malloc");
        return NULL;
    }
    new_node->name = ft_strdup(var);
    if (value)
        new_node->value = ft_strdup(value);
    else
        new_node->value = ft_strdup("");
    if (!new_node->name || !new_node->value)
    {
        perror("malloc");
        free(new_node->name);
        free(new_node->value);
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

void update_or_add_env(t_name **env, const char *var, const char *value)
{
    t_name  *current;
    t_name  *prev;
    t_name  *new_node;

    current = *env;
    prev = NULL;
    while (current)
    {
        if (ft_strcmp(current->name, var) == 0)
        {
            update_node(current, value);
            return;
        }
        prev = current;
        current = current->next;
    }
    new_node = create_new_node(var, value);
    if (!new_node)
        return;
    if (prev)
        prev->next = new_node;
    else
        *env = new_node;
}

void handle_no_cmd(t_name **env)
{
    t_name *env_copy;

    env_copy = copy_env(*env);
    if (!env_copy)
        return ;
    print_export(env_copy);
    free_env(env_copy);
}

void    process_cmd(t_name **env, char **cmd, int i)
{
    char *eq_pos;
    char *var;
    char *value;

    eq_pos = ft_strchr(cmd[i], '=');
    var = cmd[i];
    value = NULL;
    if (eq_pos)
    {
        *eq_pos = '\0';
        value = eq_pos + 1;
    }
    if (!is_valid_identifier(var))
    {
        ft_putstr_fd("minishell: export: `", 2);
        ft_putstr_fd(var, 2);
        ft_putstr_fd("`: not a valid identifier\n", 2);
        g_var.exit_s = 1;
        return ;
    }
    update_or_add_env(env, var, value);
    if (eq_pos)
        *eq_pos = '=';
}

void my_export(t_name **env, char **cmd)
{
    int i;

    g_var.exit_s = 0;
    if (cmd[1] == NULL)
    {
        handle_no_cmd(env);
        return;
    }
    i = 1;
    while (cmd[i])
    {
        process_cmd(env, cmd, i);
        i++;
    }
}
