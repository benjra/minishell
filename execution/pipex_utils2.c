#include "../parsing/mini.h"

void	child_process(t_lsttoken *token, int pipe_nb, int builtin_nb,
		t_name *env)
{
	int	fd;

	g_var.last_child_id = fork();
	if (g_var.last_child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		files_redirections(token, builtin_nb != -1);
		if (builtin_nb == -1)
			validate_cmd(token);
		if (token->is_heredoc && g_var.is_heredoc_last)
		{
			fd = open_heredoc_file(1);
			dup2(fd, 0);
			if (fd > 2)
				close(fd);
		}
		else if (g_var.pre_pipe_infd != -1 && !token->in_fd_set)
			dup2(g_var.pre_pipe_infd, 0);
		if (g_var.size != pipe_nb + 1 && !token->out_fd_set)
			dup2(token->pipe_fd[1], 1);
		if (token->pipe_fd[1] > 2)
			close(token->pipe_fd[1]);
		if (token->pipe_fd[0] > 2)
			close(token->pipe_fd[0]);
		execs(token, builtin_nb, env);
	}
}

void	in_file_prep(t_lsttoken *token, char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		g_var.exit_s = errno;
		g_var.red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var.size > 1)
			exit(1);
	}
	else
	{
		token->in_fd_set = 1;
		if ((token->redirections->type != 6 || !g_var.is_heredoc_last)
			&& !is_builtin)
			dup2(fd, 0);
		if (fd > 2)
			close(fd);
	}
}

void	out_file_prep(t_lsttoken *token, char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
	{
		g_var.exit_s = errno;
		g_var.red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var.size > 1)
			exit(1);
	}
	else
	{
		token->out_fd_set = 1;
		if (!is_builtin || g_var.size > 1)
		{
			dup2(fd, 1);
			if (fd > 2)
				close(fd);
		}
		else
			g_var.out_fd = fd;
	}
}

void	append_file_prep(t_lsttoken *token, char *path, int is_builtin)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		g_var.exit_s = errno;
		g_var.red_error = 1;
		ft_putstr_fd("minishell: ", 2);
		perror(path);
		if (!is_builtin || g_var.size > 1)
			exit(1);
	}
	else
	{
		token->out_fd_set = 1;
		if (!is_builtin || g_var.size > 1)
		{
			dup2(fd, 1);
			if (fd > 2)
				close(fd);
		}
		else
			g_var.out_fd = fd;
	}
}

int	check_builtin(t_lsttoken *token)
{
	if (!ft_strcmp("cd", token->args[0]))
		return (1);
	else if (!ft_strcmp("echo", token->args[0]))
		return (2);
	else if (!ft_strcmp("env", token->args[0]))
		return (3);
	else if (!ft_strcmp("exit", token->args[0]))
		return (4);
	else if (!ft_strcmp("export", token->args[0]))
		return (5);
	else if (!ft_strcmp("pwd", token->args[0]))
		return (6);
	else if (!ft_strcmp("unset", token->args[0]))
		return (7);
	else
		return (-1);
}
