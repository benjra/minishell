#include "mini.h"



void parsing(char *str)
{
	
	char **string ;
	int count=0;
	string=split_string(str,&count);
	t_token *list = fill_list(string);
	printf_err(list);
	//check the errors here is better
	free_tokens(string,count);
	t_lsttoken *list2=fill_token(list);
	freelist1(list);
	t_lsttoken *current = list2; // Start with the head of the list

int i=0;
while (current) 
{
	
	i = 0;
	while (current->args != NULL && current->args[i] != NULL)
	    printf("args : -- %s  ", current->args[i++]);
	printf("\n");
	while (current->redirections != NULL)
	{
	    printf("red : -- %s \n", current->redirections->red);
		current->redirections = current->redirections->next;
	}
    current = current->next; 
}
		
    // if(pipe_frst(str)==0 || double_pipe(str)==0)
    //     printf("error near `|' \n");
    // else 
    //     printf("good\n");

	//syntax errors
} 