#include "mini.h"

void parsing(char *str,t_name *env)
{
	
	char **string ;
	int count=0;
	string=split_string(str,&count);
	t_token *list = fill_list(string);
	printf_err(list);//SHOULD handle single and double quotes
	free_tokens(string,count);
	t_lsttoken *list2=fill_token(list);
	freelist1(list);
	expander(list2,env);

	// t_lsttoken *current = list2; // Start with the head of the list
	
	// while (list)
	// {
	// 	printf("%s: %d\n",list->value,list->type);
	// 	list=list->next;
	// }

// int i=0;
// while (current) 
// {
	
// 	i = 0;
// 	while (current->args != NULL && current->args[i] != NULL)
// 	    printf("args : -- %s  ", current->args[i++]);
// 	printf("\n");
// 	while (current->redirections != NULL)
// 	{
// 	    printf("red : -- %s \n", current->redirections->red);
// 		current->redirections = current->redirections->next;
// 	}
// 	    current = current->next; 
// }
} 