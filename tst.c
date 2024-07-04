// void join(char *s1,char *s2)
// {
//     int i=0;
//     int j=0;
//     size_t len1=ft_strlen(s1);
//     size_t len2=ft_strlen(s2);
//     char *join=malloc(len1+len2+1);
//     if(!join)
//         return NULL;
//     if(s1 || s2)
//         return NULL;
//     while (s1[i])
// 	{
// 		join[j++] = s1[i++];
// 	}
// 	i = 0;
// 	while (s2[i])
// 	{
// 		join[j++] = s2[i++];
// 	}
//     join[j]='\0';
//     return (join);
// }
// int main()
// {
//     char *str="hi hello everyone";
//     char **strtrim=ft_split(str);
//     int i=0;
//     while(strtrim)
//         printf("%s",strtrim[i++]);
//     }