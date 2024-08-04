#include "mini.h"

char	*get_variable(char *s)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((char *)s + i);
}
void search(char *arg)
{
    int totallen;
    int ln_aftdoll;
    int ln_befdoll;
    char *afterdol;
    char *var;
    char *befordoll;
    afterdol=ft_strchr(arg,'$');
    *afterdol='\0';
    afterdol++;
    var=get_variable(afterdol);//return the name of variable to a special caracters
    befordoll=ft_strdup(arg);
    totallen=ft_strlen(arg);
    ln_befdoll=totallen-ft_strlen(afterdol);
    ln_aftdoll=totallen-ln_befdoll;
    printf("\n<<<<  after $=> %s  >>>>\nBEFORE %s\n",afterdol,befordoll);
    
}
// char *env_search(t_name *env,char **args)
// {
    
// }


void expander(t_lsttoken *tokens,t_name *env)
{
    t_lsttoken *tmp;
    (void)env;
    tmp=tokens;
    while (tmp)
    {
        int i=0;
        while (tmp->args[i])
        {
            if(ft_strchr(tmp->args[i],'$'))
            {
               search(tmp->args[i]);
            }
            i++;
        }
        tmp=tmp->next;
        
    }
    
}