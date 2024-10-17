#include "../parsing/mini.h"

void	exec_builtin(int builtin_nb, t_lsttoken *token, t_name *env)
{
	if (builtin_nb == 1 && !g_var.red_error)
		my_cd(env, token->args);
	else if (builtin_nb == 2 && !g_var.red_error)
		my_echo(token->args);
	else if (builtin_nb == 3 && !g_var.red_error)
		my_env(env, token->args);
	else if (builtin_nb == 4 && !g_var.red_error)
		my_exit(token->args, token);
	else if (builtin_nb == 5 && !g_var.red_error)
		my_export(&env, token->args);
	else if (builtin_nb == 6 && !g_var.red_error)
		my_pwd(env, token->args);
	else if (builtin_nb == 7 && !g_var.red_error)
		my_unset(&env, token->args);
	if (g_var.out_fd > 2)
		close(g_var.out_fd);
	g_var.out_fd = 1;
}

int	check_file_errors(char *path, int builtin)
{
	if (path && (path[0] == '$' || (path[0] == '"' && path[1] == '$')))
	{
		g_var.red_error = 1;
		g_var.exit_s = 1;
		if (path[0] == '$' && path[1])
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(path, 2);
			ft_putstr_fd(" ambiguous redirect\n", 2);
		}
		else
			ft_putstr_fd("minishell: No such file or directory\n", 2);
		if (builtin)
			return (1);
		else
			exit(1);
	}
	return (0);
}

int	check_path(char *path, int is_builtin)
{
	char		*folders;
	struct stat	statbuf;
	int			i;

	if (ft_strchr(path, '/') == 0)
		return (1);
	i = ft_strlen(path);
	while (i != 0 && path[i] != '/')
		i--;
	folders = malloc(i + 2);
	if (!folders)
	{
		perror("");
		exit(errno);
	}
	lista_add_front(g_var.alist, lista_new(folders));
	my_strncpy(folders, path, i + 1);
	if (stat(folders, &statbuf) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (is_builtin)
		{
			g_var.red_error = 1;
			g_var.exit_s = 1;
			return (0);
		}
		else
			exit(1);
	}
	return (1);
}

void	files_redirections(t_lsttoken *token, int builtin)
{
	char	*path;
	t_redir	*curr_red;

	curr_red = token->redirections;
	while (curr_red)
	{
		path = curr_red->red;
		if (check_file_errors(path, builtin))
			break ;
		path = r_quotes(curr_red->red);
		if (!check_path(path, builtin))
			break ;
		if (curr_red->type == 3)
			in_file_prep(token, path, builtin);
		else if (curr_red->type == 4)
			out_file_prep(token, path, builtin);
		else if (curr_red->type == 5)
			append_file_prep(token, path, builtin);
		curr_red = curr_red->next;
	}
}

void	execute_pipes(t_lsttoken *token, int pipe_nb, t_name *env)
{
	int	builtin_nb;

	builtin_nb = check_builtin(token);
	if (g_var.size == 1 && builtin_nb != -1)
	{
		files_redirections(token, 1);
		exec_builtin(builtin_nb, token, env);
	}
	else
	{
		if (g_var.size != pipe_nb + 1)
			pipe(token->pipe_fd);
		child_process(token, pipe_nb, builtin_nb, env);
		if (token->pipe_fd[1] > 2)
			close(token->pipe_fd[1]);
		if (g_var.pre_pipe_infd > 2)
			close(g_var.pre_pipe_infd);
	}
}
