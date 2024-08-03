#include "mini.h"

void	handler(int signum)
{
	(void)signum;
	write(0, "\n", 1);
	rl_on_new_line();
	// replace the current line with newone
	rl_replace_line("", 0);
	// redisplay the input line 
	rl_redisplay();
}
int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1)
	{
		write(1, "there is no need of arguments here", 35);
		return (1);
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	program_name(env);
}