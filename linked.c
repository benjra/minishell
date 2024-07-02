#include "mini.h"

t_name	*tail(t_name *list)
{
	t_name	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}


void	ft_lstadd_back(t_name **lst, t_name *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
		tail(*lst)->next = new;
}
t_name	*ft_lstnew(char *name, char *value)
{
	t_name	*linked_lst;

	linked_lst = malloc(sizeof(t_name));
	if (!linked_lst)
		return (NULL);
	linked_lst->name = name;
	linked_lst->value = value;
	linked_lst->next = NULL;
	return (linked_lst);
}
t_name *fill_env(char **env)
{
    char *name;
    char *value;
    int i=0;
    t_name *lst;
    lst=NULL;
    while(env[i])
    {
        
    }
}