#include "header.h"

void	d_quotes(char *input, char *output, int *inside_d_quotes,
		int *inside_s_quotes, int *i, int *j)
{
	if (*inside_d_quotes)
	{
		if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
		{
			output[(*j)++] = '\"';
			output[(*j)++] = ' ';
		}
		else
			output[(*j)++] = '\"';
	}
	else
	{
		if (*i > 0 && input[*i - 1] != ' ' && output[*j - 1] != ' '
			&& !(*inside_s_quotes))
			output[(*j)++] = ' ';
		output[(*j)++] = '\"';
	}
	*inside_d_quotes = !(*inside_d_quotes);
}

void	s_quotes(char *input, char *output, int *inside_d_quotes,
		int *inside_s_quotes, int *i, int *j)
{
	if (*inside_s_quotes)
	{
		if (input[*i + 1] != ' ' && input[*i + 1] != '\0')
		{
			output[(*j)++] = '\'';
			output[(*j)++] = ' ';
		}
		else
			output[(*j)++] = '\'';
	}
	else
	{
		if (*i > 0 && input[*i - 1] != ' ' && output[*j - 1] != ' '
			&& !(*inside_d_quotes))
			output[(*j)++] = ' ';
		output[(*j)++] = '\'';
	}
	*inside_s_quotes = !(*inside_s_quotes);
}

char	*fix_quotes(char *input)
{
	t_index	index;
	char	*output;

	memset(&index, 0, sizeof(index));
	index.size = count_len(input);
	output = (char *)malloc(index.size * 3);
	if (output == NULL)
		return (NULL);
	while (input[index.i] != '\0')
	{
		if (input[index.i] == '\"' && !index.inside_s_quotes)
			d_quotes(input, output, &index.inside_d_quotes,
				&index.inside_s_quotes, &index.i, &index.j);
		else if (input[index.i] == '\'' && !index.inside_d_quotes)
			s_quotes(input, output, &index.inside_d_quotes,
				&index.inside_s_quotes, &index.i, &index.j);
		else
			output[index.j++] = input[index.i];
		index.i++;
	}
	output[index.j] = '\0';
	return (output);
}
