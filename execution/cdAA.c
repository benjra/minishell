#include "../parsing/mini.h"

void change_env(t_data *data, char **env)
{
    int i = 0;
    while (env[i])
    {
        if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
        {
            env[i] = ft_strjoinn("OLDPWD=", data->oldpwd);
        }
        if (ft_strncmp(env[i], "PWD=", 4) == 0)
            env[i]=ft_strjoinn("PWD=",data->newpwd);
        i++;
    }
}
void ft_cd(t_data *data, char **env)
{
    char *home = getenv("HOME");
    char *tmp = getcwd(NULL, 0);

    if (tmp == NULL)
    {
        perror("getcwd");
        return;
    }
    if (data->cmd[1] == NULL)
    {
        if (home != NULL)
        {
            if (chdir(home) == 0)
            {
                data->newpwd = ft_strdup(home);
                data->oldpwd = tmp;
                change_env(data, env);
            }
            else
            {
                write(2, "bash: ",7);

            perror(home);
            }
        }
            else
               write(2, "bash: cd: HOME not set\n", 23);
        free(tmp);
        return;
    }
    if (data->cmd[2] != NULL)
    {
        write(2, "bash: cd: too many arguments\n", 29);
        free(tmp);
        return;
    }
    if (chdir(data->cmd[1]) != 0)
    {
        write(2, "bash: cd: ", 10);
        perror(data->cmd[1]);
    }
    else
    {
        data->newpwd = getcwd(NULL, 0);
        data->oldpwd = tmp;
        change_env(data, env);
    }
    free(tmp);
}