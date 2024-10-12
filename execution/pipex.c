#include "../parsing/mini.h"
#include <termios.h>


void	in_file_prep(const char *path)
{
    int		fd;
    char	*trimmed_path;

    trimmed_path = trim_spaces((char *)path);
    fd = open(trimmed_path, O_RDONLY);
    if (fd == -1)
        error(trimmed_path, 1);
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void	out_file_prep(const char *path)
{
    int		fd;
    char	*trimmed_path;

    trimmed_path = trim_spaces((char *)path);
    fd = open(trimmed_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        error(trimmed_path, 1);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void	append_file_prep(const char *path)
{
    int		fd;
    char	*trimmed_path;

    trimmed_path = trim_spaces((char *)path);
    fd = open(trimmed_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
        error(trimmed_path, 1);
    dup2(fd, STDOUT_FILENO);
    close(fd);
}

void	read_heredoc(const char *delimiter, char *tmpfile)
{
    char	*line;
    int		fd;

    line = NULL;
    fd = mkstemp(tmpfile);
    if (fd == -1)
        error("heredoc", 1);
    while (1)
    {
        line = readline("> ");
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break ;
        }
        ft_putendl_fd(line,fd);
        free(line);
        line = NULL;
    }
    close(fd);
}

void	handle_redirections(t_lsttoken *cmd)
{
    t_redir	*redir;
    char	heredoc_tmpfile[] = "/tmp/heredoc_tmpXXXXXX";
    int		fd;

    redir = cmd->redirections;
    while (redir)
    {
        if (redir->type == TOKEN_REDIR_IN)
            in_file_prep(redir->red);
        else if (redir->type == TOKEN_REDIR_OUT)
            out_file_prep(redir->red);
        else if (redir->type == TOKEN_REDIR_APPEND)
            append_file_prep(redir->red);
        else if (redir->type == TOKEN_REDIR_HEREDOC)
        {
            read_heredoc(redir->red, heredoc_tmpfile);
            fd = open(heredoc_tmpfile, O_RDONLY);
            if (fd == -1)
                error("heredoc", 1);
            if (dup2(fd, STDIN_FILENO) == -1)
                error("dup2", 1);
            close(fd);
        }
        redir = redir->next;
    }
    unlink(heredoc_tmpfile);
}

int is_builtin(char **args, t_name *env)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (my_echo(args), 0);
    else if (ft_strcmp(args[0], "cd") == 0)
        return (my_cd(env, args), 0);
    else if (ft_strcmp(args[0], "pwd") == 0)
        return (my_pwd(env), 0);
    else if (ft_strcmp(args[0], "env") == 0)
        return (my_env(env, args), 0);
    else if (ft_strcmp(args[0], "export") == 0)
        return (my_export(env, args), 0);
    else if (ft_strcmp(args[0], "exit") == 0)
        return (my_exit(args), 0);
    else if (ft_strcmp(args[0], "unset") == 0)
        return (my_unset(&env, args), 0);
    else
        return (1);
}

void	execute_pipeline(t_lsttoken *commands, t_name *ev)
{
    int			pipefd[2];
    int			prev_pipe;
    pid_t		pid;
    t_lsttoken	*cmd;
    char *resolved_cmd;

    prev_pipe = -1;
    cmd = commands;
    while (cmd != NULL)
    {
        if (cmd->next != NULL)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                gl_ex = 1;
                exit(gl_ex);
            }
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            gl_ex = 1;
            exit(gl_ex);
        }
        if (pid == 0)
        {
            if (prev_pipe != -1)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }
            if (cmd->next != NULL)
            {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }
            if (is_builtin(cmd->args, ev) == 0)
            {
                if (cmd->next != NULL)
                    exit(gl_ex);
            }
            else
            {
                resolved_cmd = get_path1(cmd->args, ev);
                if (resolved_cmd)
                {
                    execve(resolved_cmd, cmd->args, ev->ev);
                    perror("execve");
                    gl_ex = 1;
                    exit(gl_ex);
                }
                else
                {
                    ft_putstr_fd(cmd->args[0], STDERR_FILENO);
                    ft_putstr_fd(": command not found", STDERR_FILENO);
                    ft_putstr_fd("\n", STDERR_FILENO);
                    gl_ex = 1;
                    exit(gl_ex);
                }
            }
        }
        else
        {
            if (prev_pipe != -1)
                close(prev_pipe);
            if (cmd->next != NULL)
                close(pipefd[1]);
            prev_pipe = pipefd[0];
        }
        cmd = cmd->next;
    }
    while (wait(NULL) > 0)
        ;
}

int	execute_args(t_lsttoken token, t_name *env)
{
    char	**args;
    int		saved_stdin;
    int		saved_stdout;

    args = token.args;
    gl_ex = 0;
    saved_stdin = dup(STDIN_FILENO);
    saved_stdout = dup(STDOUT_FILENO);
    handle_redirections(&token);
    if (args[0] != NULL)
        execute_pipeline(&token, env);
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
    return (0);
}

