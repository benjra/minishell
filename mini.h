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
#define    TOKEN_ENV_VAR 7, // For environment variables

typedef struct s_token
{
    int type;
    char        *value;
    struct s_token *next;
}   t_token;

typedef struct s_redir
{
	int				type;
	struct s_redir	*next;
	struct s_redir	*prev;
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
void parsing(char *str);
int pipe_frst(char *str);
char **split_string(char *str, int *count);
t_token *fill_list(char **lst);
void parse_and_add_token(t_token **list, const char *str, char *c, int type);
//test
char	**my_split(char const *s, char c);

#endif