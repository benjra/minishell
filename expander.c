#include "mini.h"

char	*get_specialcar(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] !=' ' && ft_isalnum(s[i]))//case of - underscore
	{
		i++;
	}
	return (s + i);
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
    totallen=ft_strlen(arg);
    ln_befdoll=totallen-ft_strlen(afterdol);
    ln_aftdoll=totallen-ln_befdoll;
    var=ft_substr(afterdol,0,ln_aftdoll-ft_strlen(get_specialcar(afterdol)));//return the name of variable to a special caracters
    befordoll=ft_strdup(arg);
    printf("\n<<<<  after $=> %s  >>>>\nBEFORE %s\n ==> var: %s\n",afterdol,befordoll,var);
    
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