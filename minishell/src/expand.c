#include "header.h"


char *find_dollar(char *str)
{
	int i = 0;
	int j = -1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i;
			i++; 
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
			{
				i++;
			}
			break;
		}
		i++;
	}
	if (j == -1)
		return NULL;
	char *substring = malloc(sizeof(char) * (i - j));
	ft_strlcpy(substring, &str[j + 1], i - j);
	return (substring);
}

void quotes(x_node *p_list, char *env)
{
	int i = 0;
	char *expand = getenv(env);
	while (p_list->str[i])
	{
		if (p_list->str[0] == '"')
		{
			while (p_list->str[i] != '$')
				i++;
			char *temp = NULL;
			p_list->str = ft_strjoin(temp, expand);
			free(temp);
		}
	}
	//p_list->str = getenv(env);
}


void expand(x_node *p_list)
{
	x_node *temp = p_list;
	while (temp)
	{
		char *str = find_dollar(temp->str);
		if (str != NULL)
		{
			quotes(temp, str);
			free(str);
		}
		temp = temp->next;
	}
	print(p_list);
}
