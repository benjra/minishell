#include "../parsing/mini.h"

void my_pwd(t_name *env)
{
    char    cwd[PATH_MAX];
  //  char    *tmp;
    t_name *tmp = env;
    int flag = 0;
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_putstr_fd(cwd, 1);
        ft_putstr_fd("\n", 1);
        //g_var.errnoo = 0;
    }
    else
    {
        while(tmp)
        {
            if(ft_strncmp(tmp->name,"PWD",3) == 0)
            {
                ft_putstr_fd(tmp->value, 1);
                ft_putstr_fd("\n", 1);
                flag = 1;
                return ;
            }
            tmp = tmp->next;
        }
        if(flag == 0)
        {
            ft_putstr_fd("execution: ", 2);
            ft_putstr_fd(strerror(errno), 2);
            ft_putstr_fd("\n", 2);
            //g_var.errnoo = errno; 
        }
    }
}
