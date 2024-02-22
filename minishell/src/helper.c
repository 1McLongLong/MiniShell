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

void remove_extra_spaces(char *str) 
{
	char *src = str;
	char *dst = str;
	int inside_quotes = 0;

	while (*src) 
	{
		if (*src == '"') 
		{
			inside_quotes = !inside_quotes;
			*dst++ = *src++;
		} 
		else if (inside_quotes || (*src != ' ' || (*(src + 1) != ' ' && *(src + 1) != '\0')))
			*dst++ = *src++;
		else
			src++;
	}
	*dst = '\0';
}

void epur_str(char *str)
{
	remove_extra_spaces(str);
	while (*str == ' ')
		str++;

	char *end = str;
	while (*end != '\0')
		end++;
	end--; 
	while (end > str && *end == ' ')
	{
		*end = '\0';
		end--;
	}
}

int str_len(const char *str) 
{
	int len = strlen(str);
	int newLen = len;
	int i = 0;
	int inquotes = 0;

	while (i < len)
	{
		if (str[i] == '"')
		{
			inquotes = !inquotes;
		}
		else if (!inquotes && (str[i] == '|' || (str[i] == '>') || (str[i] == '<')))
		{
			if (i == 0 || str[i - 1] != ' ')
			{
				newLen += 1;
			}
			if (i == len - 1 || str[i + 1] != ' ') 
			{
				newLen += 1;
			}
		}
		i++;
	}
	return (newLen);
}

/*int str_len(const char *str) 
{
	int len = strlen(str);
	int newLen = len;
	int i = 0;
	while (i < len)
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if (i == 0 || str[i - 1] != ' ')
			{
				newLen += 1;
			}
			if (i == len - 1 || str[i + 1] != ' ') 
			{
				newLen += 1;
			}
		}
		i++;
	}
	return (newLen);
}*/

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

void fix_it_again(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == ' '  && str[i + 2] == ' ' && str[i + 3] == '>')
		{
			str[j] = str[i];
			i += 3;
			j++;
		}
		else if (str[i] == '<' && str[i + 1] == ' '  && str[i + 2] == ' ' && str[i + 3] == '<')
		{
			str[j] = str[i];
			i += 3;
			j++;
		}
		str[j] = str[i];
		j++;
		i++;
	}
	str[j] = '\0';
}

