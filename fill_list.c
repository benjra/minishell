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

char *ft_strchr_skip_quotes(const char *str, char c) {
    int in_quotes = 0;
    while (*str) {
        if (*str == '"' || *str=='\'') {
            in_quotes = !in_quotes;
        } else if (*str == c && !in_quotes) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}
void parse_and_add_token(t_token **list, char *str, char c, int type) {
    char *new = ft_strchr_skip_quotes(str, c);
    if (new && strncmp(str, &c, 1)) {
        *new = '\0';
        lstadd_backs(list, lstnews(1, strdup(str)));
        lstadd_backs(list, lstnews(type, strndup(&c, 1)));
        lstadd_backs(list, lstnews(1, strdup(new + 1)));
    }
    else if (!new) 
            lstadd_backs(list, lstnews(1, strdup(str)));
     
}
 

t_token *fill_list(char **lst) {
    int i = 0;
    t_token *list = NULL;
    while (lst[i]) {
        if (strchr(lst[i], '|') || strchr(lst[i], '<') || strchr(lst[i], '>')) {
           
                if (strchr(lst[i], '|')) {
                parse_and_add_token(&list, lst[i],'|', 2);
                } else if (strchr(lst[i], '<')) {
                    parse_and_add_token(&list, lst[i], '<', 3);
                } else if (strchr(lst[i], '>')) {
                    parse_and_add_token(&list, lst[i], '>', 4);
                }
            
        } else {
            lstadd_backs(&list, lstnews(1, strdup(lst[i])));
        }
        i++;
    }
    return list;
}

