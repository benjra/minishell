/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabchou <amabchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:40:48 by amabchou          #+#    #+#             */
/*   Updated: 2024/10/21 14:55:42 by amabchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define GREENB "\033[42m"
# define BGREEN "\033[1;32m"
# define RESET_COLOR "\e[m"

typedef struct s_name
{
	char				**ev;
	char				*name;
	char				*value;
	struct s_name		*next;
}						t_name;

typedef struct s_alist
{
	void				*content;
	struct s_alist		*next;
}						t_alst;
typedef struct s_var
{
	char				*heredoc_file;
	int					exit_s;
	int					interactive;
	int					out_fd;
	int					size;
	char				**envp;
	int					pre_pipe_infd;
	pid_t				last_child_id;
	int					is_heredoc_last;
	int					red_error;
	t_alst				**alist;
}						t_var;

extern t_var			g_var;

# define TOKEN_WORD 1 // For Commands
# define TOKEN_PIPE 2 // For '|'
# define TOKEN_REDIR_IN 3 // For '<'
# define TOKEN_REDIR_OUT 4 // For '>'
# define TOKEN_REDIR_APPEND 5 // For '>>'
# define TOKEN_REDIR_HEREDOC 6 // For '<<'

typedef struct s_token
{
	int					type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_redir
{
	int					type;
	char				*red;
	struct s_redir		*next;
	struct s_redir		*previous;
}						t_redir;

typedef struct s_lsttoken
{
	int					type;
	char				**args;
	char				*cmd_path;
	t_redir				*redirections;
	struct s_lsttoken	*previous;
	struct s_lsttoken	*next;
	int					in_fd_set;
	int					is_heredoc;
	int					out_fd_set;
	int					pipe_fd[2];
	pid_t				pid;
}						t_lsttoken;

/********************** parsing *************************/

t_name					*fill_env(char **env);
void					parsing(char *str, t_name *env);
char					**split_string(char *str);
t_token					*fill_list(char **lst);
void					parse_and_add_token(t_token **list, char *str, char *c,
							int type);
t_lsttoken				*fill_token(t_token *list);
int						pipes_err(t_token *list);
int						printf_err(t_token *list);
int						ft_ambigious(t_lsttoken *list);
void					expander(t_lsttoken *tokens, t_name *env);
char					*ft_env(t_name *env, char *var);
char					*ins_quote(char *str);
void					free_env(t_name *env);
void					freelist1(t_token *list);
void					free_arg(char **args);
void					free_all(t_lsttoken *token);
t_token					*lstnews(int type, char *value);
void					lstadd_backs(t_token **lst, t_token *new);
t_token					*tails(t_token *list);
t_redir					*new_red(int type, char *red);
void					red_addback(t_redir **lst, t_redir *new);
t_redir					*last_red(t_redir *list);
void					handler(int signum);

/********************** builtins *************************/

void					my_cd(t_name *env, char **argv);
int						handle_home_directory(t_name *env, char *home);
int						try_cdpath(t_name *env, char *path, int print_path);
char					*get_env_var_value(t_name *env, const char *var);
int						update_env_vars(t_name *env, const char *oldpwd,
							const char *newpwd);
int						handle_cd_args(t_name *env, char **argv);
int						handle_tilde_expansion(t_name *env, char *arg,
							char *path);
int						print_cd_error(char *path, char *error_msg);
int						handle_directory_change(char *path, char *real_path);
int						change_directory(t_name *env, char *path, int flag,
							int print_path);
void					free_split(char **split);
int						handle_cd_dash(t_name *env);
void					my_echo(char **av);
void					my_pwd(t_name *env, char **av);
void					my_env(t_name *env, char **cmd);
void					my_export(t_name **env, char **cmd);
void					my_exit(char **argv, t_lsttoken *token);
int						ft_isspace(char c);
int						check_overflow(long long res, int sign,
							char next_digit);
void					print_numeric_error(const char *str);
void					my_unset(t_name **env, char **cmd);
int						is_valid_identifier(const char *var);
void					update_or_add_env(t_name **env, const char *var,
							const char *value);
t_name					*create_new_node(const char *var, const char *value);
void					print_export(t_name *env);
t_name					*bubble_sort_env(t_name *env);
void					swap_nodes(t_name *a, t_name *b);
void					update_node(t_name *node, const char *value);
void					handle_no_cmd(t_name **env);
void					process_cmd(t_name **env, char **cmd, int i);
t_name					*copy_env(t_name *env);

/********************** execution *************************/

void					execute_args(t_lsttoken *token, t_name *env);
void					init_g_var(t_lsttoken **token);
void					lista_add_front(t_alst **lst, t_alst *new);
t_alst					*lista_new(void *content);
void					files_redirections(t_lsttoken *token, int builtin);
void					exec_builtin(int btn, t_lsttoken *token, t_name *env);
void					sig_wait(t_lsttoken *token);
char					*just_copy(char *target, int *i);
char					*digit(char *target, int *i);
char					*gotta_expand(char *target, int flag, int *i);
char					*get_var_val(int var_index);
char					*add_something(char *str, char *add);
int						validate_var_name(char *var);
char					*my_dup(const char *s);
char					*until_dollar(char *str);
char					*exit_status(char *variable, int *i);
char					*special_cases(char *target, int *i);
void					lista_add_front(t_alst **lst, t_alst *new);
t_alst					*lista_new(void *content);
void					hd_sigint(int sig);
int						upto(char *str, char c);
char					*r_quotes(char *str);
char					*replace(char *str, char rip);
int						ft_fork(void);
void					free_str(void *ptr);
int						should_not_be_expanded(char *str);
void					print_perror(char *str, int exitt);
void					my_strncpy(char *dest, char *src, int n);
void					check_cmd_path(t_lsttoken *token);
void					check_command_name(t_lsttoken *token);
int						get_var_index(char *key);
char					*get_env_in_herdoc(char *target, int flag,
							char *delimiter);
void					read_herdoc(char *delimiter);
void					my_heredoc(t_lsttoken *token);
void					mini_heredoc(t_lsttoken *token, t_name *env);
void					exec_builtin(int btn, t_lsttoken *token, t_name *env);
int						check_file_errors(char *path, int builtin);
int						check_path(char *path, int is_builtin);
void					files_redirections(t_lsttoken *token, int builtin);
void					execute_pipes(t_lsttoken *token, int pipe_nb,
							t_name *env);
char					*put_cmd_status(int status, char *cmd_path, char *cmd);
char					*get_cmd_path(char *cmd, char **exec_programs_dirs);
void					validate_cmd(t_lsttoken *token);
void					execs(t_lsttoken *token, int btn, t_name *env);
int						open_heredoc_file(int read_only);
int						check_builtin(t_lsttoken *token);
void					append_file_prep(t_lsttoken *token, char *path,
							int is_builtin);
void					out_file_prep(t_lsttoken *token, char *path,
							int is_builtin);
void					in_file_prep(t_lsttoken *token, char *path,
							int is_builtin);
void					child_process(t_lsttoken *token, int pipe_nb, int btn,
							t_name *env);
char					*allocate_folders(char *path, int i);
void					handle_malloc_error(void);
int						handle_stat_error(char *path, int is_builtin);
void					setup_signals(void);
void					handle_pipe_redirections(t_lsttoken *token,
							int pipe_nb);
void					handle_file_redirections(t_lsttoken *token, int btn);

#endif