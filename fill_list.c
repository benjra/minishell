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
void parse_and_add_token(t_token **list, const char *str, char *c, int type) {
    (void)type;
    char *new = ft_strchr_skip_quotes(str, *c);
    if (new && ft_strncmp(str, c, 1)) {
        *new = '\0'; // Null-terminate the token
        if (*(str)) {
            // Add the token before the symbol as a new node
            lstadd_backs(list, lstnews(1, ft_strdup(str)));
        }
        // Check if there's more content after the symbol
        if (*(new + 1)) {
            new += ft_strlen(c);
            // Add the rest of the string as a new node
            lstadd_backs(list, lstnews(1, ft_strdup(new + ft_strlen(c))));
        }
    } else if (!new) {
        // If no symbol was found, add the whole string as a single token
        lstadd_backs(list, lstnews(1, ft_strdup(str)));
    }
}

// void parse_and_add_token(t_token **list, char *str, char *c, int type) {
//     (void)type;
//     char *new = ft_strchr_skip_quotes(str, *c);
//     if (new && ft_strncmp(str, c, 1)) {
//         *new = '\0';
//         if (*(str))
//             lstadd_backs(list, lstnews(1, ft_strdup(str)));
//         // lstadd_backs(list, lstnews(type, ft_strdup(c)));
//         if (*(new +1))
//         {
//             new += ft_strlen(c);
//             lstadd_backs(list, lstnews(1, ft_strdup(new + ft_strlen(c)))); //i need to add a recursion for check if theris more then symbol
//         }
//     }
//     else if (!new) 
//             lstadd_backs(list, lstnews(1, ft_strdup(str)));
     
// }

t_token *fill_list(char **lst) {
    int i = 0;
    t_token *list = NULL;
    while (lst[i]) {              
        if (ft_strchr(lst[i], '|') || ft_strchr(lst[i], '<') || ft_strchr(lst[i], '>')) {

                if (ft_strnstr(lst[i], ">>",-1) && ft_strncmp(lst[i], ">>", -1)) 
                    parse_and_add_token(&list, lst[i], ">>", 5);
                else if (ft_strnstr(lst[i], "<<",-1) && ft_strncmp(lst[i], "<<", -1)) 
                    parse_and_add_token(&list, lst[i], "<<", 6);
                else if (ft_strchr(lst[i], '|') && ft_strncmp(lst[i], "|", -1)) 
                    parse_and_add_token(&list, lst[i],"|", 2);
                else if (ft_strchr(lst[i], '<') && ft_strncmp(lst[i], "<", -1) && ft_strncmp(lst[i], "<<", -1)) 
                    parse_and_add_token(&list, lst[i], "<", 3);
                else if (ft_strchr(lst[i], '>') && ft_strncmp(lst[i], ">", -1) && ft_strncmp(lst[i], ">>", -1)) 
                    parse_and_add_token(&list, lst[i], ">", 4);
                else
                    lstadd_backs(&list, lstnews(1, ft_strdup(lst[i])));
            
        } else {
            lstadd_backs(&list, lstnews(1, ft_strdup(lst[i])));
        }
        i++;
    }
    return list;
}

