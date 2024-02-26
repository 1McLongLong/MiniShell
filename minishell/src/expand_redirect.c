#include "header.h"


static char *find_dollar(char *str)
{
	int i;
	int j;
	char *substring;
	
	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i;
			i++; 
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
				i++;
			break;
		}
		i++;
	}
	if (j == -1)
		return NULL;
	substring = malloc(sizeof(char) * (i - j));
	ft_strlcpy(substring, &str[j + 1], i - j);
	return (substring);
}

static void quotes(char **str, char *env)
{
	int i;
	int j;
	char *expand;
	char *temp;
	char *temp2;
	char *l_temp;
	int end;

	i = 0;
	j = 0;
	// char *temp2 = ft_substr(*str, j, end - j);
	// char *new_str = ft_strjoin(temp, expand);
	// char *l_temp = new_str;
	// new_str = ft_strjoin(l_temp, temp2);
	//
	// free(*str);  // Free the original str
	// *str = new_str;  // Update str to point to the modified string
	expand = getenv(env);
	temp = NULL;
	if ((*str)[0] != '$')
	{
		while ((*str)[i] != '$')
			i++;
		temp = ft_substr(*str, 0, i);
	}
	while ((*str)[j])
		j++;
	end = j;
	while (!(ft_isalpha((*str)[j])) && (*str)[j] != '_')
		j--;
	j++;
	temp2 = ft_substr(*str, j, end - j);
	*str = ft_strjoin(temp, expand);
	l_temp = *str;
	*str = ft_strjoin(l_temp, temp2);
}


void expand_redir(char **str)
{
	char *env;
	
	env = find_dollar(*str);
	if (env != NULL)
	{
		quotes(str, env);
		free(env);
	}
	return ;
}
