#include "mini.h"
void    program_name(char **en)
{
    char *prom;
    t_name *env;
    char *cmd;
    // char buffer[1024];
    env=fill_env(en);
    while(1)
    {
        prom=ft_strdup(BGreen);
        prom=join(prom,"minishell$ ");
        prom=join(prom, RESET_COLOR);
        if(!prom)
            exit(1);
        // prom=prompt();
        cmd=readline(prom);//u should know how to work with readline 
        if(!cmd)
            break;
        if (ft_strncmp(cmd, "", -1))
        {
            add_history(cmd);
            parsing(cmd,env);
	       
            // if(getcwd(buffer,104)==NULL)
            //     printf("null buffer");
            // else
            // printf("%s\n",buffer);
        }
    }
    rl_clear_history();
    //free_env() should add this func
}
