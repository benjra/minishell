#include "mini.h"
void freelist1(t_token *list)
{
    while (list != NULL)
    {
        t_token *temp = list;
        list = list->next; 
        free(temp); 
    }
    
}

