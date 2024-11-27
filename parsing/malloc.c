#include "mini.h"

void	*add_new_malloc(t_malloc *ptr, int size)
{
	t_malloc	*tmp;
	t_malloc	*new;

	new = NULL;
	tmp = ptr;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_malloc));
	if (!new)
		return (NULL);
	new->content = malloc(size);
	new->next = NULL;
	if (!new->content)
		return (NULL);
	tmp->next = new;
	return (new->content);
}
void	ft_free_list(t_malloc *ptr)
{
	t_malloc	*tmp;

	while (ptr)
	{
		tmp = ptr->next;
		if (ptr->content)
		{
			free(ptr->content);
			ptr->content = NULL;
		}
		free(ptr);
		ptr = tmp;
	}
}
void	*ft_malloc(int size, int c)
{
	static t_malloc	*ptr = 0;

	if (ptr == 0)
	{
		ptr = malloc(sizeof(t_malloc));
		if (!ptr)
			return (NULL);
		ptr->content = NULL;
		ptr->next = NULL;
	}
	if (c == -1)
	{
		ft_free_list(ptr);
		ptr = 0;
	}
	else
		return (add_new_malloc(ptr, size));
	return (0);
}
