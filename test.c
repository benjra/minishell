#include <ctype.h> 
#include "mini.h"

int is_space(char str)
{
    if (str == ' ' || str == '\n' || str == '\t' || str == '\v' || str == '\f' || str == '\r')
        return (1);
    return (0);
}
int countwrd(char *str)
{
    int i = 0;
    int len = 0;
    int in_quotes = 0;

    while (str[i])
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            in_quotes = !in_quotes;
            i++;
            while (str[i] && !(str[i] == '"' || str[i] == '\''))
                i++;
        }
        if (is_space(str[i]) || str[i] == '\0')
        {
            if (!isspace(str[i - 1]) && !in_quotes)
                len++;
        }
        i++;
    }
    return len + 1;
}
int	len(char *s, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}
char **split_string(char *str, int *count)
{
    char **tokens;
    int token_count;
    int in_quotes;
    char *start;
    char *token;
    size_t len;

    tokens = malloc(sizeof(char *) * (countwrd((char *)str) + 1));// should modify the max tokens
    token_count = 0;
    in_quotes = 0;
    start = str;
    if (!str || !*str)
        return (NULL);
    while (*str)
    {
        if (*str == '"' || *str == '\'')
        {
            in_quotes = !in_quotes;
        }
        else if (is_space(*str) && !in_quotes)
        {
            if (start != str)
            {
                len = str - start;
                token = malloc(len + 1);
                strncpy(token, start, len);
                token[len] = '\0';
                tokens[token_count++] = token;
            }
            start = str + 1;
        }
        str++;
    }
    if (start != str)
    {
        len = str - start;
        token = malloc(len + 1);
        strncpy(token, start, len);
        token[len] = '\0';
        tokens[token_count++] = token;
    }
    tokens[token_count] = NULL;
    *count = token_count;
    return (tokens);
}
// int main()
// {
//     // char *str="hi "hello bouchra"'how are u' 18";
//     // int len=countwrd("hi 'hello bouchra''how are u' 18");
//     char **string=split_string("hi 'hello bouchra''how are u' 18",0);
//     printf("com : %s , %s , %s\n",string[0],string[1],string[2]);
//     return 0;
// }