#include "mini.h"

int pipe_frst(char *tmp)
{
    int i=0;
    char *str;
	if (!tmp || !*tmp)
		return 1;
    str = ft_strtrim(tmp , "\t " );
	if (!str || !*str)
		return 1;
    i=ft_strlen(str);
    if(str[i-1]=='|' || str[0]=='|')
    {
		return 0;
	}
    return 1;
}

int double_pipe(char *tmp)
{
	int i=0;
    char *str; 
    str = ft_strtrim(tmp , "\t " );
	while(str[i])
	{
		if(str[i]=='|' )
		{
				if(str[i+1]=='|')
					return 0;
				while(str[i+1] && (str[i+1]!=' ' || str[i+1]!='\t'))
				{
					i++;
					if(str[i+1]=='|' )
						return 0;
				}
		}
		i++;
	}
	return 1;
}


void parsing(char *str)
{
	char **string ;
	int count=0;
	string=split_string(str,&count);
	// int i=0;
	t_token *list = fill_list(string);
	t_lsttoken *list2=fill_token(*(list));
	t_lsttoken *current = list2; // Start with the head of the list
int i=0;
while (current!= NULL ) {
    printf("%s \n %s\n %d \n", current->args[i++], current->redirections->red ,current->redirections->type);
    current = current->next; // Move to the next node
}
		
    if(pipe_frst(str)==0 || double_pipe(str)==0)
        printf("error near `|' \n");
    else 
        printf("good\n");
}