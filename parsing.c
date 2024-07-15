#include "mini.h"

int pipe_frst(char *tmp)
{
    int i=0;
    char *str;
    str = ft_strtrim(tmp , "\t " );
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
t_token *current = list; // Start with the head of the list

while (current!= NULL ) {
    printf("%s : %d\n", current->value, current->type);
    // i++; // Increment i regardless of whether we move to the next node
    current = current->next; // Move to the next node
}
		
	//syntax error
    if(pipe_frst(str)==0 || double_pipe(str)==0)
        printf("error near `|' \n");
    else 
        printf("good\n");
}