#ifndef MINI_H
#define MINI_H

# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
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

typedef struct list1
{
    char *str;
    struct list1 *next;
} t_list1;

char    **ft_split(char *str);
int ft_strlen(char *str);
void prompt();

void    program_name(char **en);
t_name *fill_env(char **env);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

#endif