#include "mini.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arrlen(char **av)
{
    int i;
    int j;
    int len;
    len=0;
    i=0;
    while(av[i])
    {
        j=0;
        while(av[i][j]==' ')
            j++;
        while(av[i][j])
        {
            if(av[i][j]!=' ')
                len++;
            j++;
        }
        i++;
    }
    return (len);
}

char	*tstring(char **av, int len)
{
	int		i;
	int		j;
	char	*str;
	int		k;

	i = 1;
	j = 0;
	k = 0;
	str = malloc((len + 1) * sizeof(char *));
	if (!str)
		{
            free(str);
            return NULL;
        }
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			str[k++] = av[i][j++];
			if (av[i][j] == '\0')
				str[k++] = ' ';
		}
		i++;
	}
	str[k - 1] = '\0';
	return (str);
}

// t_token *fill_list(char **lst)
// {
//     int type;
//     char *value;
//     int i=0;
//     t_token *list;
//     list=NULL;
// 	// int j=0;
// 	//should change the strchr to another one skipp the symbols inside quotes 
//     while(lst[i])
//     {		
// 		if((ft_strchr(lst[i],'|')
// 			|| ft_strchr(lst[i],'<') 
// 			|| ft_strchr(lst[i],'>') 
// 			|| ft_strnstr(lst[i],"<<",-1) 
// 			|| ft_strnstr(lst[i],">>",-1)))
// 		 {
// 						char *new=NULL;
// 			if(ft_strchr(lst[i],'|') && ft_strncmp(lst[i] , "|", 2))
// 			{				

// 						new=ft_strchr(lst[i],'|');
// 						*new = 0 ;
// 						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
// 						lstadd_backs(&list,lstnews(2,ft_strdup("|")));
// 						lstadd_backs(&list,lstnews(1,ft_strdup(new + 1)));
						
// 			}			else if(ft_strchr(lst[i],'<') && ft_strncmp(lst[i] , "<", 2))
// 			{	
// 								new=ft_strchr(lst[i],'<');
// 						*new = 0 ;
// 						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
// 						lstadd_backs(&list,lstnews(3,ft_strdup("<")));
// 						lstadd_backs(&list,lstnews(1,ft_strdup(new + 1)));

// 			}			else if(ft_strchr(lst[i],'>') && ft_strncmp(lst[i] , ">", 2))
// 			{				
// 							new=ft_strchr(lst[i],'>');
// 						*new = 0 ;
// 						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
// 						lstadd_backs(&list,lstnews(4,ft_strdup(">")));
// 						lstadd_backs(&list,lstnews(1,ft_strdup(new + 1)));
// 			}			else if(ft_strnstr(lst[i],"<<",-1) && ft_strncmp(lst[i] , "<<", 2))
// 			{	
// 							new=ft_strnstr(lst[i],"<<",-1);
// 						*new = 0 ;
// 						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
// 						lstadd_backs(&list,lstnews(6,ft_strdup("<<")));
// 						lstadd_backs(&list,lstnews(1,ft_strdup(new + 2)));

// 			}			else if(ft_strnstr(lst[i],">>",-1) && ft_strncmp(lst[i] , ">>", 2))
// 			{				
// 						new=ft_strnstr(lst[i],">>",-1);
// 						*new = 0 ;//handle thhis case it doesnt work 
// 						lstadd_backs(&list,lstnews(1,ft_strdup(lst[i])));
// 						lstadd_backs(&list,lstnews(5,ft_strdup(">>")));
// 						lstadd_backs(&list,lstnews(1,ft_strdup(new + 2)));
// 			}			
// 	 		*new=0;
// 			new++;
// 			lstadd_backs(&list,lstnews(type,new));
// 			}
// 			else
// 			{
// 				value=ft_strdup(lst[i]);
// 				type=1;
// 				lstadd_backs(&list,lstnews(type,value));
// 			} 
// 		i++;
//     }
// 	return(list); 
// }
