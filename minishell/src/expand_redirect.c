#include "header.h"

static char	*find_dollar(char *str)
{
	char	*substring;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i;
			i++; 
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
				i++;
			break ;
		}
		i++;
	}
	if (j == -1)
		return (NULL);
	substring = malloc(sizeof(char) * (i - j));
	ft_strlcpy(substring, &str[j + 1], i - j);
	return (substring);
}

static void	quotes(char **str, char *env)
{
	t_index	index;
	char	*expand;
	char	*temp;
	char	*temp2;
	char	*l_temp;
	int		end;

	index.i = 0;
	index.j = 0;
	expand = getenv(env);
	temp = NULL;
	if ((*str)[0] != '$')
	{
		while ((*str)[index.i] != '$')
			index.i++;
		temp = ft_substr(*str, 0, index.i);
	}
	while ((*str)[index.j])
		index.j++;
	end = index.j;
	while (!(ft_isalpha((*str)[index.j])) && (*str)[index.j] != '_')
		index.j--;
	index.j++;
	temp2 = ft_substr(*str, index.j, end - index.j);
	*str = ft_strjoin(temp, expand);
	l_temp = *str;
	*str = ft_strjoin(l_temp, temp2);
}


void	expand_redir(char **str)
{
	char	*env;

	env = find_dollar(*str);
	if (env != NULL)
	{
		quotes(str, env);
		free(env);
	}
	return ;
}
