#include "mini.h"

 t_redir *last_red(t_redir *list)
{
    t_redir *temp;

    if (!list) 
        return NULL;
    temp = list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    return temp; 
}

void	red_addback(t_redir **lst, t_redir *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
    {
        last_red(*lst)->next = new;
		new->next=NULL;
        new->previous=last_red(*lst);
    }
}
t_redir	*new_red(int type,char *red)
{
	t_redir	*linked_lst;

	linked_lst = malloc(sizeof(t_redir));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
		
	linked_lst->type = type;
	linked_lst->red=red;
	linked_lst->next = NULL;
    linked_lst->previous= NULL;
	return (linked_lst);
}
///llstoken--------------------
t_lsttoken	*last(t_lsttoken *list)
{
	t_lsttoken	*temp;

	temp = list;
	if (!list)
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return (temp);
}

void	add_back(t_lsttoken **lst, t_lsttoken *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
	}
	else
    {
        last(*lst)->next = new;
		new->next = NULL;
        new->previous=last(*lst);
    }
}

t_lsttoken	*newnode(int type, char **args,t_redir *redirection)
{
	t_lsttoken	*linked_lst;

	linked_lst = malloc(sizeof(t_lsttoken));
	if (!linked_lst)
	{
		free(linked_lst);
		return (NULL);
	}
		
	linked_lst->type = type;
	linked_lst->args = args;
    // red_addback(redirection,new_red(int type));
	linked_lst->redirections=redirection;
	linked_lst->next = NULL;
    linked_lst->previous= NULL;
	return (linked_lst);
}
int len(t_token *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		// printf ("%d\n", lst->type);
		if (lst->type ==2)
			break;
		if((lst->type>=3 && lst->type<=6))
		{
			lst = lst->next;
		}
		else
			i++;
		lst = lst->next;
	}
	return (i);
}


t_lsttoken *fill_token(t_token *list)
{
	t_token	*temp;
	t_lsttoken *token=NULL;
	t_lsttoken *token1=NULL;
	t_redir redirections;

	int i=0; 
	temp = list;
	token=malloc(sizeof(t_lsttoken));
	if(!token)
		free(token);
	token->args =ft_calloc(len(list)+1*sizeof(char *),1);
	// ft_putnbr_fd(len(list), 1);
	token1 =  token;
	while(temp!=NULL)
	{	
		if(temp->type>=2 && temp->type<=6)
		{
			red_addback(&(token->redirections),new_red(temp->type,ft_strdup(temp->next->value)));
			//the debuging stop here and also in the function last_red
			temp = temp->next;
		}
		if(temp->type==2)
		{
			add_back(&token,newnode(temp->type,token->args,&redirections));
			token = token->next;
			token->args = ft_calloc(len(temp->next)+1*sizeof(char *),1);
			if ((token->args = realloc(token->args, (i + 2) * sizeof(char*))) == NULL) 
				free(token->args);
			i=0;
		}
		else
		{		
				token->args[i++]=ft_strdup(temp->value);
		}
		if (temp && temp->value) {
    		if ((token->args = realloc(token->args, (i + 2) * sizeof(char*))) == NULL) 
    	    	free(token->args);
    	token->args[i++] = ft_strdup(temp->value);
		}

		temp=temp->next;
	}

	return token;
}

// t_lsttoken *fill_token(t_token *list)
// {
//     t_token *temp = list;
//     t_lsttoken *token = NULL;
//     t_lsttoken *current_token = NULL;
//     t_redir redirections;
//     char **args = NULL;
//     int num_args = 0;

//     while (temp != NULL)
//     {
//         if (temp->type >= 2 && temp->type <= 6)
//         {
//             // Assuming red_addback and new_red are defined elsewhere
//             red_addback(&(token->redirections), new_red(temp->type, ft_strdup(temp->next->value)));
//             temp = temp->next;
//         }

//         if (temp->type == 2)
//         {
//             // Allocate memory for args based on the number of arguments processed so far
//             args = realloc(args, (num_args + 1) * sizeof(char *));
//             if (!args)
//                 return NULL; // Handle memory allocation failure

//             args[num_args++] = ft_strdup(temp->value);
//         }

//         // Create a new node for the token list
//         t_lsttoken *new_node = malloc(sizeof(t_lsttoken));
//         if (!new_node)
//         {
//             free(args); // Clean up allocated memory if node creation fails
//             return NULL;
//         }

//         // Initialize the new node (assuming you have a constructor function or set methods)
//         init_new_node(new_node, temp->type, args, &redirections);

//         // Link the new node to the existing list
//         if (token == NULL)
//         {
//             token = new_node;
//             current_token = new_node;
//         }
//         else
//         {
//             current_token->next = new_node;
//             current_token = new_node;
//         }

//         temp = temp->next;
//     }

//     return token;
// }
