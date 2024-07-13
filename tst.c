// // void join(char *s1,char *s2)
// // {
// //     int i=0;
// //     int j=0;
// //     size_t len1=ft_strlen(s1);
// //     size_t len2=ft_strlen(s2);
// //     char *join=malloc(len1+len2+1);
// //     if(!join)
// //         return NULL;
// //     if(s1 || s2)
// //         return NULL;
// //     while (s1[i])
// // 	{
// // 		join[j++] = s1[i++];
// // 	}
// // 	i = 0;
// // 	while (s2[i])
// // 	{
// // 		join[j++] = s2[i++];
// // 	}
// //     join[j]='\0';
// //     return (join);
// // }
// #include <stdio.h>
// int is_quotes(char c)
// {
//   if(c=='\'' || c=='"')
//     return 1;
//   return 0;
// }
// int symbols(char c)
// {
//   if(c='<' || c=='>' || c='>>' || c='<<')
//     return 1;
//   return 0;
// }
// int collect_string(char **str)
// {
// 	 int i=0;
	 
// }
// void fill_lista( char *str)
// {
//   int i=0;
//   int start=0;
//   int end=0;
//   char *new;
//   while(str[i])
//   {
//   if(is_quotes(str[i]))
//     {
//       if(is_quotes(str[i+1]))
//     }
//   while(str[i] && !is_quotes(str[i]))
//     i++;

//   }
// }


// static int	countword(char *str, char sep)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] == sep)
// 			i++;
// 		if (str[i])
// 			len++;
// 		while (str[i] && str[i] != sep)
// 			i++;
// 	}
// 	return (len);
// }

// static int	len_word(char *s, char c)
// {
// 	int	i;
// 	int	len;

// 	len = 0;
// 	i = 0;
// 	while (s[i] && s[i] != c)
// 	{
// 		len++;
// 		i++;
// 	}
// 	return (len);
// }

// static char	*alloc(char *s, char c)
// {
// 	char	*string;
// 	int		lenght;
// 	int		i;

// 	i = 0;
// 	lenght = len_word((char *)s, c);
// 	string = malloc(sizeof(char) * (lenght + 1));
// 	if (!string)
// 		return (NULL);
// 	while (i < lenght && s[i])
// 	{
// 		string[i] = s[i];
// 		i++;
// 	}
// 	string[i] = '\0';
// 	return (string);
// }

// static char	**free_split(char **str, int i)
// {
// 	while (i >= 0)
// 	{
// 		// free(str[i]);
// 		i--;
// 	}
// 	free(str);
// 	return (NULL);
// }

// // char	**my_split(char const *s, char c)
// // {
// // 	char	**string;
// // 	int		index_string;

// // 	index_string = 0;
// // 	if (!s)
// // 		return (NULL);
// // 	string = (char **)malloc(sizeof(char *) * (countword((char *)s, c) + 1));
// // 	if (!string)
// // 		return (NULL);
// // 	while (*s)
// // 	{
// // 		while (*s && (*s == c || *s=='|' || *s == '<'  || *s == '>' ))
// // 			s++;
// // 		if (*s)
// // 		{
// // 			string[index_string] = alloc((char *)s, c);
// // 			if (!string[index_string])
// // 				return (free_split(string, index_string));
// // 			index_string++;
// // 		}
// // 		while (*s && *s != c )
// // 			s++;
// // 	}
// // 	string[index_string] = NULL;
// // 	return (string);
// // }

// // int main()
// // {
// //     char *str="hi hello everyone";
// //     char **strtrim=ft_split(str);
// //     int i=0;
// //     while(strtrim)
// //         printf("%s",strtrim[i++]);
// //     }