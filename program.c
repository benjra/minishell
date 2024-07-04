#include "mini.h"
void    program_name(char **en)
{
    // char *prom;
    t_name *env;
    char *cmd;
    env=fill_env(en);
    // int i=0;
    while(1)
    {

        prom=ft_strdup(BGreen);
        prom=join(prom,">>")
        cmd=readline("hi put somthing ");//u should know how to work with readline 
        if(!cmd)
            break;
        printf("%s\n",cmd);
        // free(prom);
    }
}
