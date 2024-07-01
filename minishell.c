int main(int ac,char **av,char **env)
{
    if(ac!=1)
    {
        printf("there is no need of arguments here");
        exit(0);
    }
    // ignore_signals();
    prompt();
    signal(SIGINT, SIG_IGN);
    signal(SIQUIT, SIG_IGN);
}