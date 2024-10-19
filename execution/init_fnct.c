#include "../parsing/mini.h"

void	init_g_var(t_lsttoken **token)
{
	t_lsttoken	*current;

	g_var.is_heredoc_last = 0;
	g_var.red_error = 0;
	g_var.pre_pipe_infd = -1;
	g_var.last_child_id = 0;
	g_var.size = 0;
	g_var.interactive = 1;
	g_var.out_fd = 1;
	current = *token;
	while (current)
	{
		current->in_fd_set = 0;
		current->out_fd_set = 0;
		current = current->next;
	}
}
