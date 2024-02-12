#include "header.h"


void	ft_free(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}

void epur_str(char *str) 
{
	int i = 0;
	int j = 0;

	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
		str[j++] = str[i++];

	while (str[i]) 
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			str[j++] = ' ';
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			str[j++] = str[i++];
	}
	str[j] = '\0';
}

int str_len(const char *str) 
{
	int len = strlen(str);
	int newLen = len; // Start with the length of the original string

	int i = 0;
	while (i < len) 
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<') 
		{
			if (i == 0 || str[i - 1] != ' ')
			{
				newLen += 1; // Add 1 for the space before
			}
			if (i == len - 1 || str[i + 1] != ' ') 
			{
				newLen += 1; // Add 1 for the space after
			}
		}
		i++;
	}
	return (newLen);
}

int get_len(char *str)
{
	int i = 0;
	int len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '\\' || str[i] == '/' || str[i] == '(' || str[i] == ')')
		{
			len++;
			i++;
		}
		else 
			i++;
	}
	return (len);
}
