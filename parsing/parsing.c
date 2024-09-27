#include "mini.h"
int count_args(char **args)
{
    int count = 0;
    while (args[count] != NULL)
    {
        count++;
    }
    return count;
}

void set_num_cmds(t_lsttoken *lsttoken)
{
    if (lsttoken && lsttoken->args)
    {
        lsttoken->num_cmds = count_args(lsttoken->args);
    }
}

void parsing(char *str,t_name *env)
{
	(void)env;
	char **string ;
	int count=0;
	string=split_string(str,&count);
	t_token *list = fill_list(string);
	// int i=0;
	// while(string[i])
	// 	printf("string: %s\n",string[i++]);
	free_tokens(string,count);
	if (printf_err(list))
	{
		freelist1(list);
		return ;
	}
	t_lsttoken *list2=fill_token(list);
	freelist1(list);
	expander(list2,env);// should expand also redirections in the opening of files
	// ft_ambigious(list2);// segf in "" && 
	
	// while (list)
	// {
	// 	printf("%s: %d\n",list->value,list->type);
	// 	list=list->next;
	// }



t_lsttoken *current= list2; // Start with the head of the list
// while (current) 
// {
	
// 	int i = 0;
// 	while (current->args != NULL && current->args[i] != NULL)
// 	    printf("args : ----%s  \n", current->args[i++]);
// 	while (current->redirections)
// 	{
// 	    printf("red : -- %s \n", current->redirections->red);
// 		current->redirections = current->redirections->next;
// 	}
// 	current = current->next;

// }
	set_num_cmds(current);
	//printf("Number of commands: %d\n", current->num_cmds);
	execute_args(*current, env); //builtins
	free_all(current);

}

//  make comments for the executor && change the errors messages: ----fggr"fje  