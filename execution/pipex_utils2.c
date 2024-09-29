#include "../parsing/mini.h"

char	*get_path(t_name *env, char *cmd)
{
    char *path = get_env_var_value(env, "PATH");

    if (path)
        return path;

    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(" :No such file or directory\n", STDERR_FILENO);
    exit(1);
}

int	is_valid_variable(const char *var)
{
    int	i;

    if (var == NULL || !ft_isalpha(var[0]))
        return (0);
    i = 1;
    while (var[i] != '\0')
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

char	*check_path(char **p, char *cmd)
{
    int		i;
    char	*t;
    char	*tem;

    i = 0;
    if (cmd == NULL || cmd[0] == '\0' || ft_strcmp(cmd, "..") == 0 || ft_strcmp(cmd, "$") == 0)
	{
        ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
        ex = 127;
		exit(ex);
	}
    while (p[i])
    {
        tem = ft_strjoin(p[i], "/");
        t = ft_strjoin(tem, cmd);
        free(tem);
        if (access(t, X_OK) == 0)
            return (t);
        free(t);
        i++;
    }
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": command not found", STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    ex = 127;
    exit(ex);
}

char	*get_path1(char **cmd, t_name *ev)
{
    char	*bpath;
    char	**paths;
    char	*path1;

    if (ft_strchr(cmd[0], '/') || ft_strncmp(cmd[0], "./", 2) == 0)
    {
        if (access(cmd[0], X_OK) == 0)
            return (cmd[0]);
        else
            error(cmd[0], 126);
    }
    bpath = get_path(ev, cmd[0]);
    paths = ft_split(bpath, ':');
    path1 = check_path(paths, cmd[0]);
    ft_free(paths);
    return (path1);
}
