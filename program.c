#include "mini.h"
void    program_name(char **en)
{
    char *prom;
    t_name *env;
    char *cmd;
    (void)en;
    env=fill_env(en);
    while(1)
    {

        prom=ft_strdup(BGreen);
        prom=join(prom,">>"); //why it doesnt work
        prom=prompt();
        cmd=readline(prom);//u should know how to work with readline 
        add_history(cmd);
        parsing(cmd);
        if(!cmd)
            break;
        // printf("%s\n",cmd);
        free(prom);
    }
    rl_clear_history();
    //free_env() should add this func
}
