#include "mini.h"

void parsing(char *str,t_name *env)
{
	(void)env;
	char **string ;
	int count=0;
	string=split_string(str,&count);
	t_token *list = fill_list(string);
	if (printf_err(list))
		return ;
	free_tokens(string,count);
	t_lsttoken *list2=fill_token(list);
	// freelist1(list);
	expander(list2,env);// should expand also redirections in the opening of files
	// ft_ambigious(list2);// segf in "" && 

	
	// while (list)
	// {
	// 	printf("%s: %d\n",list->value,list->type);
	// 	list=list->next;
	// }

int i=0;
// // while(string[i])
// // 	printf("string: %s\n",string[i++]);

t_lsttoken *current = list2; // Start with the head of the list
while (current) 
{
	
	i = 0;
	while (current->args != NULL && current->args[i] != NULL)
	    printf("args : ----%s  \n", current->args[i++]);
	while (current->redirections != NULL)
	{
	    printf("red : -- %s \n", current->redirections->red);
		current->redirections = current->redirections->next;
	}
	    current = current->next; 
	
	// free_all(current);
	}
	gl_var = 0;
} 

  
//  make comments for the executor && change the errors messages: ----fggr"fje  