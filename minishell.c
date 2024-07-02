#include "mini.h"
#include <signal.h>
int main(int ac,char **av,char **env)
{
    if(ac!=1)
    {
        write(1,"there is no need of arguments here",35);
        return 1;
    }
    // ignore_signals();
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    program_name(env);
}