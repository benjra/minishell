#ifndef MINI_H
#define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
#include <sys/wait.h>
#include <errno.h>
# include <string.h>

extern int gl_var;
extern int ex;
# define GREENB  "\033[42m"       //# Red
# define BGreen "\033[1;32m"       //# Green      //# White
# define RESET_COLOR "\e[m"

// typedef struct s_redir;

typedef struct s_name
{
    char **ev;
    char *name;
    char *value;
    struct s_name *next;
}t_name;

#define     TOKEN_WORD          1      // For Commands
#define    TOKEN_PIPE           2      // For '|'
#define    TOKEN_REDIR_IN       3  // For '<'
#define    TOKEN_REDIR_OUT      4 // For '>'
#define    TOKEN_REDIR_APPEND   5 // For '>>'
#define    TOKEN_REDIR_HEREDOC  6 // For '<<'

typedef struct s_token
{
    int type;
    char        *value;
    struct s_token *next;
}   t_token;

typedef struct s_redir
{
	int				type;
    char *red;
	struct s_redir	*next;
	struct s_redir	*previous;
}	t_redir;

typedef struct s_lsttoken
{
    int type;
    char **args;
    t_redir *redirections;
    struct s_lsttoken *previous;
    struct s_lsttoken *next;
    int num_cmds;
}   t_lsttoken;


void    program_name(char **en);
t_name *fill_env(char **env);
void parsing(char *str,t_name *env);
// int pipe_frst(char *str);
char **split_string(char *str, int *count);
t_token *fill_list(char **lst);
void parse_and_add_token(t_token **list, char *str, char *c, int type);
t_lsttoken *fill_token(t_token *list);
//errors functions
int pipes_err(t_token *list);
t_token	*tails(t_token *list);
int printf_err(t_token *list);
void ft_ambigious(t_lsttoken *list);
//expand 
void expander(t_lsttoken *tokens,t_name *env);
char *ft_env(t_name *env,char *var);
char *ins_quote(char *str);
//free
void free_tokens(char **tokens, int count) ;
void free_env(t_name *env);
void freelist1(t_token *list);
void	free_all(t_lsttoken *token);

//node list
t_token	*lstnews(int type, char *value);
void	lstadd_backs(t_token **lst, t_token *new);
t_token	*tails(t_token *list);



//builtins
int my_cd(t_name *env, char **argv);
int my_echo(char **av);
void my_pwd(t_name *env);
int my_env(t_name *env, char **cmd);
void my_export(t_name *env, char **cmd);
int my_exit(char **argv);
void my_unset(t_name **env, char **cmd);
int	is_valid_variable(const char *var);

//execution
int execute_args(t_lsttoken token,t_name *env);
int count_args(char **args);
void set_num_cmds(t_lsttoken *lsttoken);
void execute_pipeline(t_lsttoken *commands, t_name *ev);
char *get_path1(char **cmd, t_name *ev);
void read_heredoc(const char *delimiter, char *tmpfile);
void in_file_prep(const char *path);
void out_file_prep(const char *path);
void append_file_prep(const char *path);
void handle_redirections(t_lsttoken *cmd);
char *get_path(t_name *env, char *cmd);
char *check_path(char **p, char *cmd);
int change_directory(t_name *env, char *path, int flag);
char *get_env_var_value(t_name *env, const char *var);
void	update_or_add_env(t_name **env, const char *var, const char *value);
char	*trim_spaces(char *str);
void	error(const char *s, int ss);
void	ft_free(char **av);
char	*skipp(char *str);
int is_builtin(char **args, t_name *env);
#endif