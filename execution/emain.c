#include "../parsing/mini.h"

int     ft_pwd(void);
void    ft_echo(char *str, int n);
void    ft_exit(void);
void    ft_env(char **my_env);
int     ft_cd(const char *pathname);
char *ft_strjoinn(char *s1, char *ss2)
{
	int i;
	int j;
	char *result;

	if (!s1 && !ss2)
		return (NULL);
	if (!s1)
		return ((char *)ss2);
	if (!ss2)
		return ((char *)s1);
	i = ft_strlen(s1);
	j = ft_strlen(ss2);
	result = ((char *)malloc(i + j + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, i);
	ft_memcpy(result + i, ss2, j);
	result[i + j] = '\0';
	return (result);
}
int main(int ac, char **av, char **env) 
{
    char *pathname = av[1];
    // if (chdir(pathname) != 0)
    // {
    //     perror("chdir");
    //     return (1);
    // }
    // printf("Directory changed to %s\n", pathname);
    // return (0);
    if (ac == 2)
        ft_cd(av[1]);
    else
        wait(NULL);
}
