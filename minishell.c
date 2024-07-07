#include "mini.h"
int main(int ac,char **av,char **env)
{
    (void) av;
    if(ac!=1)
    {
        write(1,"there is no need of arguments here",35);
        return 1;
    }
    // ignore_signals();
    signal(SIGINT, handler);//create a function that print \n and handle this y using somme functs
    signal(SIGQUIT, SIG_IGN);//shouldnt make it here
    program_name(env);
}