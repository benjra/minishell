#ifndef MINI_H
#define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
#include <sys/wait.h>


# define DCOLORB "\033[49m"
# define GREENB  "\033[42m"
# define BBlack "\033[1;30m"       //# Black
# define BRed "\033[1;31m"         //# Red
# define BGreen "\033[1;32m"       //# Green
# define BYellow "\033[1;33m"      //# Yellow
# define BBlue "\033[1;34m"        //# Blue
# define BPurple "\033[1;35m"       //# Purple
# define BCyan "\033[1;36m"       //# Cyan
# define BWhite "\033[1;37m"       //# White
#define RESET_COLOR "\e[m"

// typedef struct s_redir;

typedef struct s_name
{
    char *name;
    char *value;
    struct s_name *next;
}t_name;


#define  TOKEN_WORD 1,      // For Commands
#define    TOKEN_PIPE 2,      // For '|'
#define    TOKEN_REDIR_IN 3,  // For '<'
#define    TOKEN_REDIR_OUT 4, // For '>'
#define    TOKEN_REDIR_APPEND 5, // For '>>'
#define    TOKEN_REDIR_HEREDOC 6, // For '<<'

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
}t_lsttoken;


char *prompt();
void    program_name(char **en);
t_name *fill_env(char **env);
char *join(char *s1,char *s2);
void get_prompt(char **dst,char *str);
void parsing(char *str,t_name *env);
int pipe_frst(char *str);
char **split_string(char *str, int *count);
t_token *fill_list(char **lst);
void parse_and_add_token(t_token **list, char *str, char *c, int type);
t_lsttoken *fill_token(t_token *list);
//errors functions
int pipes_err(t_token *list);
t_token	*tails(t_token *list);
void printf_err(t_token *list);
//expand 
void expander(t_lsttoken *tokens,t_name *env);
char *ft_env(t_name *env,char *var);
void rm_quotes(t_lsttoken *tokens);
//free
void free_tokens(char **tokens, int count) ;
void free_env(t_name *env);
void freelist1(t_token *list);
#endif