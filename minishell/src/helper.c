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

void	remove_extra_spaces(char *str)
{
	char	*src;
	char	*dst;
	int		inside_quotes;

	src = str;
	dst = str;
	inside_quotes = 0;
	while (*src)
	{
		if (*src == '"')
		{
			inside_quotes = !inside_quotes;
			*dst++ = *src++;
		}
		else if (inside_quotes
			|| (*src != ' ' || (*(src + 1) != ' ' && *(src + 1) != '\0')))
			*dst++ = *src++;
		else
			src++;
	}
	*dst = '\0';
}

void	epur_str(char *str)
{
	char	*end;

	remove_extra_spaces(str);
	while (*str == ' ')
		str++;
	end = str;
	while (*end != '\0')
		end++;
	end--;
	while (end > str && *end == ' ')
	{
		*end = '\0';
		end--;
	}
}

int	str_len(char *str)
{
	int	len;
	int	newlen;
	int	i;
	int	inquotes;

	len = strlen(str);
	newlen = len;
	i = 0;
	inquotes = 0;
	while (i < len)
	{
		if (str[i] == '"')
			inquotes = !inquotes;
		else if (!inquotes && (str[i] == '|' || (str[i] == '>')
				|| (str[i] == '<')))
		{
			if (i == 0 || str[i - 1] != ' ')
				newlen += 1;
			if (i == len - 1 || str[i + 1] != ' ')
				newlen += 1;
		}
		i++;
	}
	return (newlen);
}

int	get_len(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '\\'
			|| str[i] == '/' || str[i] == '(' || str[i] == ')')
		{
			len++;
			i++;
		}
		else
			i++;
	}
	return (len);
}

void	fix_it_again(char *str)
{
	t_index	index;

	memset(&index, 0, sizeof(index));
	while (str[index.i])
	{
		if (str[index.i] == '>' && str[index.i + 1] == ' '
			&& str[index.i + 2] == ' ' && str[index.i + 3] == '>')
		{
			str[index.j] = str[index.i];
			index.i += 3;
			index.j++;
		}
		else if (str[index.i] == '<' && str[index.i + 1] == ' '
			&& str[index.i + 2] == ' ' && str[index.i + 3] == '<')
		{
			str[index.j] = str[index.i];
			index.i += 3;
			index.j++;
		}
		str[index.j] = str[index.i];
		index.j++;
		index.i++;
	}
	str[index.j] = '\0';
}
