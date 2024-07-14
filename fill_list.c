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
    while(lst[i])
    {
		if(ft_strchr(lst[i],'|') || ft_strchr(lst[i],'<') || ft_strchr(lst[i],'>'))
		{
			int j=0;
			while(lst[i][j])
			{
				//should do somethin here 
				// if()
				//for each symbols you should make a node + make her type too here 
			}
		}
        else
        {
            value=ft_strdup(lst[i]);
			// if(ft_strncmp(value,"|"))
				type=1;

        } 
		lstadd_backs(&list,lstnews(type,value));
		i++;
    }
	return(list); 
}
// if(ft_strchr(lst[i],'|') || ft_strchr(lst[i],'>') || ft_strchr(lst[i],'<'))
