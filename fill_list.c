#include "mini.h"

t_token	*tails(t_token *list)
{
	t_token	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}


void	lstadd_backs(t_token **lst, t_token *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		tails(*lst)->next = new;
}
t_token	*lstnews(int type, char *value)
{
	t_token	*linked_lst;

	linked_lst = malloc(sizeof(t_token));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
		
	linked_lst->type = type;
	linked_lst->value = value;
	linked_lst->next = NULL;
	return (linked_lst);
}

t_token *fill_list(char **lst)
{
    int type;
    char *value;
    int i=0;
    t_token *list;
    list=NULL;
	int j=0;
	//should change the strchr to another one skipp the symbols inside quotes 
    while(lst[i])
    {		
		if((lst[i][j]!='"' && lst[i][j]!='\'') && (ft_strchr(lst[i],'|') || ft_strchr(lst[i],'<') || ft_strchr(lst[i],'>') || ft_strnstr(lst[i],"<<",-1) || ft_strnstr(lst[i],">>",-1)))
		{
						char *new=NULL;
						if(ft_strchr(lst[i],'|'))
			{				
						new=ft_strdup("|");
						type=2;
						lstadd_backs(&list,lstnews(type,new));
						new=ft_strchr(lst[i],'|');
						type=1;
			}			else if(ft_strchr(lst[i],'<'))
			{	
							new=ft_strdup("<");
							type=3;
							lstadd_backs(&list,lstnews(type,new));

							new=ft_strchr(lst[i],'<');
							type=1;

			}			else if(ft_strchr(lst[i],'>'))
			{				
						new=ft_strdup(">");
						type=4;
						lstadd_backs(&list,lstnews(type,new));
						new=ft_strchr(lst[i],'>');
						type=1;
			}			else if(ft_strnstr(lst[i],"<<",-1))
			{	
						new=ft_strdup("<<");
						type=6;
						lstadd_backs(&list,lstnews(type,new));			
						new=ft_strnstr(lst[i],"<<",-1);
							type=1;

			}			else if(ft_strnstr(lst[i],">>",-1))
			{				
						new=ft_strdup(">>");
						type=5;
						lstadd_backs(&list,lstnews(type,new));	
						// free(new);
						new=ft_strnstr(lst[i],">>",-1);
							type=1;
			}			
	 		*new=0;
			new++;
		lstadd_backs(&list,lstnews(type,new));
		}
        else
        {
            value=ft_strdup(lst[i]);
				type=1;
        } 
		lstadd_backs(&list,lstnews(type,value));
		i++;
    }
	return(list); 
}
// if(ft_strchr(lst[i],'|') || ft_strchr(lst[i],'>') || ft_strchr(lst[i],'<'))
