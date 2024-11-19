/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:18:20 by amabchou          #+#    #+#             */
/*   Updated: 2024/11/19 12:12:25 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "../our_libft/libft.h"
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
	int					exit_s;
	int					interactive;
	int					out_fd;
	int					size;
	int					flag;
	int					i;
	char				**envp;
	int					pre_pipe_infd;
	pid_t				last_child_id;
	int					is_heredoc_last;
	int					red_error;
	t_alst				**alist;
	char				*fd;
	int					btn;
	char				**hd_files;
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
	int					expand;
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
void					handle_symbol_token(t_token **list, char *str, char *c,
							int type);
void					handle_no_symbol_token(t_token **list, char *str,
							char *c);
void					parse_and_add_token(t_token **list, char *str, char *c,
							int type);
char					*ft_strchr_skip_quotes(const char *str, char *c);
int						get_type(char *lst);
void					check_symbols(char *str, t_token **list);
int						double_symb(t_token *list);
int						countwrd(char *str);
int						skip_quotes_in_count(char *str, int i);
int						is_space(char str);
char					*ft_strncpy(char *dest, char *src, unsigned int n);
void					skip_quotes(char **str);
char					*get_word(char *str, int *i);
char					*search_env(int len, char *afterdoll, t_name *env);
char					*search(char *arg, t_name *env);
void					free_env_array(char **env_array);
char					**env_to_array(t_name *env);
void					sync_env_array(t_name *env);
t_lsttoken				*last(t_lsttoken *list);
void					add_back(t_lsttoken **lst, t_lsttoken *new);
t_lsttoken				*newnode(int type, char **args);
char					*loop_through_string(char *tmp2, char *exp_,
							t_name *env);
void					normi_quotes(char *str, char **exp_, t_name *env);
char					*process_word(char *str, char *exp_, t_name *env);
char					*init_tmp_vars(char *args, char **exp_);
char					*ft_strnstr1(const char *haystack, const char *needle,
							size_t len);
char					*small_expand(char *args, t_name *env);
char	*ft_strchr1(const char *s, int c);
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
char					*create_env_string(t_name *env_node);
void					my_export(t_name **env, char **cmd);
void					my_exit(char **argv, t_lsttoken *token);
int						ft_isspace(char c);
int						check_overflow(long long res, int sign,
							char next_digit);
void					print_numeric_error(const char *str);
void					my_unset(t_name **env, char **cmd);
int						is_valid_identifier(const char *var);
void					update_or_add_env(t_name **env, const char *var,
							const char *value, int had_equals);
t_name					*create_new_node(const char *var, const char *value,
							int had_equals);
void					print_export(t_name *env);
t_name					*bubble_sort_env(t_name *env);
void					swap_nodes(t_name *a, t_name *b);
void					update_node(t_name *node, const char *value);
void					handle_no_cmd(t_name **env);
void					process_cmd(t_name **env, char **cmd, int i);
t_name					*copy_env(t_name *env);
t_name					*find_env_var(t_name *env, const char *var);
char					**env_to_array(t_name *env);
void					sync_env_array(t_name *env);
char					*set_node_value(const char *value);
void					free_node_contents(t_name *node);
void					update_existing_node(t_name *current, const char *value,
							int had_equals);
t_name					*create_and_init_node(const char *var,
							const char *value, int had_equals);
void					handle_invalid_identifier(const char *cmd);
void					update_or_add_env_part1(t_name **env, const char *var,
							t_name **prev, t_name **current);

/********************** execution *************************/

void					execute_args(t_lsttoken *token, t_name *env);
void					init_g_var(t_lsttoken **token);
void					lista_add_front(t_alst **lst, t_alst *new);
t_alst					*lista_new(void *content);
void					files_redirections(t_lsttoken *token, int builtin);
void					exec_builtin(int btn, t_lsttoken *token, t_name *env);
void					sig_wait(t_lsttoken *token);
char					*until_dollar(char *str);
void					hd_sigint(int sig);
char					*r_quotes(char *str);
char					*replace(char *str, char rip);
void					print_perror(char *str, int exitt);
void					my_strncpy(char *dest, char *src, int n);
void					check_cmd_path(t_lsttoken *token);
void					check_command_name(t_lsttoken *token);
int						get_var_index(char *key);
int						check_file_errors(char *path, int builtin);
int						check_path(char *path, int is_builtin);
void					execute_pipes(t_lsttoken *token, int pipe_nb,
							t_name *env);
char					*put_cmd_status(int status, char *cmd_path, char *cmd);
char					*get_cmd_path(char *cmd, char **exec_programs_dirs);
void					validate_cmd(t_lsttoken *token);
void					execs(t_lsttoken *token, int btn, t_name *env);
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
int						handle_stat_error(char *path, int is_builtin);
void					handle_pipe_redirections(t_lsttoken *token,
							int pipe_nb);
void					handle_file_redirections(t_lsttoken *token, int btn);
char					*hdfile(int i);
void					free_heredoc(int exit_s, char *s, t_name *env,
							t_lsttoken *token);
char					*hdexpand(char *l);
int						ft_heredoc(int i, t_lsttoken *token, t_name *env);
void					handle_signals(int mode);

char					*small_expand__(char *args, t_name *env);
char					*get_word__(char *str, int *i);
#endif