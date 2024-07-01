void ignore_signals(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIQUIT, SIG_IGN);
}