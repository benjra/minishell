#include "mini.h"
// int skip(char *s,int i)
// {
//     i++;
//     while(s[i])
//     {
//         if(s[i]!='"' && s[i]!='\'')
//             i++;
//     }
//     return i;
// }
// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
//     while(s[i])
//     {
//         if(s[i]=='"' || s[i]=='\'')
//             i=skip((char *)s,i);
//         while(s[i] != (const char)c)
//         {
//             if (s[i] == '\0')
//             {
//                 return (0);
//             }
//             i++;
//         }
//     }
	
// 	return ((char *)s + i);
// }

char *join(char *s1,char *s2)
{
    int i=0;
    int j=0;
    size_t len1=ft_strlen(s1);
    size_t len2=ft_strlen(s2);
    char *join=malloc(len1+len2+1);
    if(!join)
        return NULL;
    if(!s1 || !s2)
        return NULL;
    while (s1[i])
	{
		join[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		join[j++] = s2[i++];
	}
    join[j]='\0';
    return (join);
}
void get_prompt(char **dst,char *str)
{
	char *tmp;
	tmp=join(*dst,str);
	free(*dst);
	*dst=tmp;
}