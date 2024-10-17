#include "mini.h"

void	count_total_cmds(t_lsttoken *head)
{
    int	tot_cmds;

	tot_cmds = 0;
    t_lsttoken *current = head;

    while (current != NULL)
    {
		tot_cmds++;
        current = current->next;
    }
	g_var.size = tot_cmds;
}
void	alistclear(t_alst **lista)
{
	t_alst	*tmp;

	while (*lista)
	{
		tmp = (*lista)->next;
		if (*lista && (*lista)->content)
			free((*lista)->content);
		if (*lista)
			free(*lista);
		(*lista) = tmp;
	}
}

void	parsing(char *str, t_name *env)
{
	char		**string;
	t_token		*list;
	t_lsttoken	*list2;
	t_lsttoken	*current;

	g_var.alist = malloc(sizeof(t_alst *));
	*(g_var.alist) = NULL;
	string = split_string(str);
	list = fill_list(string);
	free_arg(string);
	if (printf_err(list))
	{
		freelist1(list);
		return ;
	}
	list2 = fill_token(list);
	freelist1(list);
	expander(list2, env);
	current= list2;
	init_g_var(&current);
    count_total_cmds(current);
	execute_args(current, env);
	alistclear(g_var.alist);
	free_all(current);
}
