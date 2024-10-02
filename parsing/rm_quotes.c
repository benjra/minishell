#include "mini.h"

char	*handle_quote(char *str, int *len)
{
	char	c;
	int		i;
	char	*substr;

	c = str[*len];
	(*len)++;
	i = *len;
	while (str[*len] && str[*len] != c)
		(*len)++;
	substr = ft_substr(str, i, *len - i);
	if (str[*len])
		(*len)++;
	return (substr);
}

char	*ins_quote(char *str)
{
	int i = 0;
	int len = 0;
	char *res = ft_strdup("");
	char *tmp[2];

	while (str[len])
	{
		tmp[0] = res;
		if (str[len] == '"' || str[len] == '\'')
			tmp[1] = handle_quote(str, &len);
		else
		{
			i = len;
			while (str[len] && str[len] != '"' && str[len] != '\'')
				len++;
			tmp[1] = ft_substr(str, i, len - i);
		}
		res = ft_strjoin(res, tmp[1]);
		free(tmp[1]);
		free(tmp[0]);
	}
	return (res);
}