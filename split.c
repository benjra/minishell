#include "mini.h"
#define MAX_TOKENS 100
char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int is_space(char str)
{
    if(str==' ')
        return 1;
    return 0;
}
char **split_string(char *str, int *count) {
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));

    int token_count = 0;
    int in_quotes = 0;
     char *start = str;
    char *token;
    if (!str || !*str)
        return NULL;
    while (*str) 
    {
        if (*str == '"' || *str=='\'') {
            in_quotes = !in_quotes;
        } else if (is_space(*str) && !in_quotes) {
            if (start != str) {
                size_t len = str - start;
                token = malloc(len + 1);
                ft_strncpy(token, start, len);
                token[len] = '\0';
                tokens[token_count++] = token;
            }
            start = str + 1;
        }
        str++;
    }

    if (start != str) {
        size_t len = str - start;
        token = malloc(len + 1);
        ft_strncpy(token, start, len);
        token[len] = '\0';
        tokens[token_count++] = token;
    }

    tokens[token_count] = NULL;
    *count = token_count;
    return tokens;
}

void free_tokens(char **tokens, int count) 
{
    for (int i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}