#include "header.h"

char	*find_dollar(char *str)
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
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
			{
				i++;
			}
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

void	quotes(x_node *p_list, char *env)
{
	char *expand;
	char *temp;
	char *temp2;
	char *l_temp;
	int i;
	int j;
	int end;

	i = 0;
	j = 0;
	while (p_list->str[i])
	{
		if (p_list->str[0] == '"')
		{
			expand = getenv(env);
			while (p_list->str[i] != '$')
				i++;
			temp = ft_substr(p_list->str, 0, i);
			while (p_list->str[j])
				j++;
			end = j;
			while (j > 0 && !(ft_isalnum(p_list->str[j])) && p_list->str[j] != '_')
				j--;
			j++;
			temp2 = ft_substr(p_list->str, j, end - j);
			free(p_list->str);
			p_list->str = ft_strjoin(temp, expand);
			l_temp = p_list->str;
			p_list->str = ft_strjoin(l_temp, temp2);
			free(temp);
			free(temp2);
		}
		else if (p_list->str[0] == '\'')
		{
			while (p_list->str[i])
				i++;
			temp = ft_substr(p_list->str, 0, i);
			free(p_list->str);
			p_list->str = strdup(temp);
			free(temp);
		}
		else
		{
			expand = getenv(env);
			temp = NULL;
			if (p_list->str[0] != '$')
			{
				while (p_list->str[i] != '$')
					i++;
				temp = ft_substr(p_list->str, 0, i);
			}
			while (p_list->str[j])
				j++;
			end = j;
			while (j >= 0 && !(ft_isalnum(p_list->str[j])) && p_list->str[j] != '_')
				j--;
			j++;
			temp2 = ft_substr(p_list->str, j, end - j);
			free(p_list->str);
			p_list->str = ft_strjoin(temp, expand);
			l_temp = p_list->str;
			p_list->str = ft_strjoin(l_temp, temp2);
			if (temp != NULL)
				free(temp);
			free(temp2);
		}
		break ;
	}
}


void	expand(p_dblst *p_list)
{
	char	*str;
	x_node	*temp;

	temp = p_list->head;
	while (temp)
	{
		str = find_dollar(temp->str);
		if (str != NULL)
		{
			quotes(temp, str);
			free(str);
			temp = temp->next;
		}
		else
			temp = temp->next;
	}
	// print(p_list);
}
