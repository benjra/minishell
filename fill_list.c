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
// void fill_node(char *new,char **lst,t_token *list)
// {
// 	int i=0;
// 						new=ft_strchr(lst[i],'|');
// 						*new = 0 ;
// 						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
// 						lstadd_backs(&list,lstnews(2,ft_strdup("|")));
// 						lstadd_backs(&list,lstnews(1,ft_strdup(new + 1)));
// }
// if(ft_strchr(lst[i],'|') || ft_strchr(lst[i],'>') || ft_strchr(lst[i],'<'))


t_token *fill_list(char **lst)
{
    int type;
    char *value;
    int i=0;
    t_token *list;
    list=NULL;
	// int j=0;
	//should change the strchr to another one skipp the symbols inside quotes 
	if (!lst || !*lst)
		return NULL;
    while(lst[i])
    {		
		if((ft_strchr(lst[i],'|')
			|| ft_strchr(lst[i],'<') 
			|| ft_strchr(lst[i],'>') 
			|| ft_strnstr(lst[i],"<<",-1) 
			|| ft_strnstr(lst[i],">>",-1)))
		 {
						char *new=NULL;
			if(ft_strchr(lst[i],'|') && ft_strncmp(lst[i] , "|", 2))
			{				

						new=ft_strchr(lst[i],'|');
						*new = 0 ;
						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
						lstadd_backs(&list,lstnews(2,ft_strdup("|")));
						lstadd_backs(&list,lstnews(1,ft_strdup(new + 1)));
						
			}			else if(ft_strchr(lst[i],'<') && ft_strncmp(lst[i] , "<", 2))
			{	
								new=ft_strchr(lst[i],'<');
						*new = 0 ;
						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
						lstadd_backs(&list,lstnews(3,ft_strdup("<")));
						lstadd_backs(&list,lstnews(1,ft_strdup(new + 1)));

			}			else if(ft_strchr(lst[i],'>') && ft_strncmp(lst[i] , ">", 2))
			{				
							new=ft_strchr(lst[i],'>');
						*new = 0 ;
						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
						lstadd_backs(&list,lstnews(4,ft_strdup(">")));
						lstadd_backs(&list,lstnews(1,ft_strdup(new + 1)));
			}			else if(ft_strnstr(lst[i],"<<",-1) && ft_strncmp(lst[i] , "<<", 2))
			{	
							new=ft_strnstr(lst[i],"<<",-1);
						*new = 0 ;
						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
						lstadd_backs(&list,lstnews(6,ft_strdup("<<")));
						lstadd_backs(&list,lstnews(1,ft_strdup(new + 2)));

			}			else if(ft_strnstr(lst[i],">>",-1) && ft_strncmp(lst[i] , ">>", 2))
			{				
						new=ft_strnstr(lst[i],">>",-1);
						*new = 0 ;//handle thhis case it doesnt work 
						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
						lstadd_backs(&list,lstnews(5,ft_strdup(">>")));
						lstadd_backs(&list,lstnews(1,ft_strdup(new + 2)));
			}			
	 		*new=0;
			new++;
			lstadd_backs(&list,lstnews(type,new));
			}
			else
			{
				value=ft_strdup(lst[i]);
				type=1;
				lstadd_backs(&list,lstnews(type,value));
			} 
		i++;
    }
	return(list); 
}
