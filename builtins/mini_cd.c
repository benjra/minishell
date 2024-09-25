#include "../parsing/mini.h"

void free_split(char **split)
{
    int i;

    if (!split)
        return;
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

int update_env_vars(t_name *env, const char *oldpwd, const char *newpwd)
{
    update_or_add_env(&env, "OLDPWD", oldpwd);
    update_or_add_env(&env, "PWD", newpwd);
    return 0;
}

char *get_env_var_value(t_name *env, const char *var)
{
    t_name *current;

    current = env;
    while (current)
    {
        if (ft_strcmp(current->name, var) == 0)
            return current->value;
        current = current->next;
    }
    return NULL;
}

int try_cdpath(t_name *env, char *path)
{
    char *cdpath;
    char try_path[1024];
    char **cdpath_dirs;
    int i = 0;

    cdpath = get_env_var_value(env, "CDPATH");
    if (!cdpath || path[0] == '/')
        return change_directory(env, path, 0);
    cdpath_dirs = ft_split(cdpath, ':');
    while (cdpath_dirs[i])
    {
        ft_strlcpy(try_path, cdpath_dirs[i], sizeof(try_path));
        ft_strlcat(try_path, "/", sizeof(try_path));
        ft_strlcat(try_path, path, sizeof(try_path));

        if (change_directory(env, try_path, 1) == 0)
        {
            free_split(cdpath_dirs);
            return 0;
        }
        i++;
    }
    free_split(cdpath_dirs);
    return change_directory(env, path, 0);
}

int change_directory(t_name *env, char *path, int flag)
{
    char oldpwd[1024];
    char newpwd[1024];

    if (getcwd(oldpwd, sizeof(oldpwd)) == NULL || chdir(path) != 0)
    {
        if (flag == 0)
        {
            ft_putstr_fd("cd: ", 2);
            ft_putstr_fd(path, 2);
            ft_putstr_fd(": ", 2);
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
        }
        return 1;
    }
    if (getcwd(newpwd, sizeof(newpwd)) == NULL)
    {
        ft_putstr_fd("cd: error retrieving new directory\n", 2);
        return 1;
    }
    return update_env_vars(env, oldpwd, newpwd);
}

int handle_home_directory(t_name *env, char *home)
{
    if (home == NULL)
    {
        ft_putstr_fd("cd: HOME not set\n", 2);
        return 1;
    }
    return change_directory(env, home, 0);
}

int handle_cd_dash(t_name *env)
{
    char *oldpwd;
    oldpwd = get_env_var_value(env, "OLDPWD");

    if (oldpwd == NULL)
    {
        ft_putstr_fd("cd: OLDPWD not set\n", 2);
        return 1;
    }

    if (change_directory(env, oldpwd, 0) == 0)
    {
        ft_putendl_fd(oldpwd, 1);
        return 0;
    }
    return 1;
}

int my_cd(t_name *env, char **argv)
{
    char path[1024];
    char *home;

    if (argv[1] && argv[2])
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return 1;
    }
    home = get_env_var_value(env, "HOME");
    if (!argv[1] || (ft_strncmp(argv[1], "~", 1) == 0 && ft_strlen(argv[1]) == 1))
        return handle_home_directory(env, home);
    if (ft_strcmp(argv[1], "-") == 0)
        return handle_cd_dash(env);
    if (argv[1][0] == '~')
    {
        if (home == NULL)
            return handle_home_directory(env, home);
        ft_strlcpy(path, home, sizeof(path));
        ft_strlcat(path, argv[1] + 1, sizeof(path));
    }
    else
        ft_strlcpy(path, argv[1], sizeof(path));
    return try_cdpath(env, path);
}
