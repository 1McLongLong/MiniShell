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
	int j = 0;
  (void)p_list;
	char *expand = getenv(env);
  if (!expand)
    return ;
	while (p_list->str[i])
	{
		if (p_list->str[0] == '"')
		{
			while (p_list->str[i] != '$')
				i++;
			char *temp = ft_substr(p_list->str, 1, i - 1);
      while (p_list->str[j])
        j++;
      int end = j;
      while (!(ft_isalpha(p_list->str[j])) && p_list->str[j] != '_')
        j--;
      j++;
      char *temp2 = ft_substr(p_list->str, j, end - j - 1);
      p_list->str = ft_strjoin(temp, expand);
      char *l_temp = p_list->str;
      p_list->str = ft_strjoin(l_temp, temp2);
		}
    else if (p_list->str[0] == '\'')
    {
    }
    else
    {
      char *temp = NULL;
      if (p_list->str[0] != '$')
      {
			  while (p_list->str[i] != '$')
			  	i++;
			  temp = ft_substr(p_list->str, 0, i);
      }
      while (p_list->str[j])
        j++;
      int end = j;
      while (!(ft_isalpha(p_list->str[j])) && p_list->str[j] != '_')
        j--;
      j++;
      char *temp2 = ft_substr(p_list->str, j, end - j);
      p_list->str = ft_strjoin(temp, expand);
      char *l_temp = p_list->str;
      p_list->str = ft_strjoin(l_temp, temp2);
    }
    break;
	}
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
		  temp = temp->next;
		}
    else
		  temp = temp->next;
	}
	print(p_list);
}
