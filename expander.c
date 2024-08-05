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
char *get_var(int len,char *afterdoll)
{
    char *var;
    var=ft_substr(afterdoll,0,len-ft_strlen(get_specialcar(afterdoll)));
    return (var);
}
char *search_env(int len,char *afterdoll,t_name *env)
{
    char *replace;
    char *var;
    var=get_var(len,afterdoll);

    replace=ft_env(env,var);
    printf("---replace: %s---",replace);
    *afterdoll+=ft_strlen(var);
    if(ft_strchr(afterdoll,'$'))
      search_env(ft_strlen(afterdoll),afterdoll,env);
    return (replace);
}
void search(char *arg,t_name *env)
{
    int totallen;
    int ln_aftdoll;
    int ln_befdoll;
    char *afterdol;
    // char *var;
    char *befordoll;
    afterdol=ft_strchr(arg,'$');
    *afterdol='\0';
    afterdol++;
    totallen=ft_strlen(arg);
    ln_befdoll=totallen-ft_strlen(afterdol);
    ln_aftdoll=totallen-ln_befdoll;
    // var=get_var(ln_aftdoll,afterdol);//return the name of variable to a special caracters
    befordoll=ft_strdup(arg);
    char *replace=search_env(ln_aftdoll,afterdol,env);
    
    printf("\n<<<<  after $=> %s  >>>>\nBEFORE %s\n<<rep: %s>>",afterdol,befordoll,replace);
    
}
// char *env_search(t_name *env,char **args)
// {
    
// }


void expander(t_lsttoken *tokens,t_name *env)
{
    t_lsttoken *tmp;
    // (void)env;
    tmp=tokens;
    while (tmp)
    {
        int i=0;
        while (tmp->args[i])
        {
            if(ft_strchr(tmp->args[i],'$'))
            {
               search(tmp->args[i],env);
            }
            i++;
        }
        tmp=tmp->next;
        
    }
    
}