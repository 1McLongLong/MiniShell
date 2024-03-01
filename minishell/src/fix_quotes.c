
#include "header.h"

int	count_len(char *input)
{
	int	size = 0;
	int	insideQuotes = 0;
	int	insideSingleQuotes = 0;
	int	i = 0;

	while (input[i] != '\0')
	{
		if (input[i] == '\"' && !insideSingleQuotes)
		{
			if (insideQuotes)
			{
				if (input[i + 1] != ' ' && input[i + 1] != '\0')
					size += 1;
				size += 1;
			}
			else
			{
				if (i > 0 && input[i - 1] != ' ' && input[i - 1] != '\0' && !insideSingleQuotes)
					size += 1;
				size += 1;
			}
			insideQuotes = !insideQuotes;
		}
		else if (input[i] == '\'' && !insideQuotes)
		{
			if (insideSingleQuotes)
			{
				if (input[i + 1] != ' ' && input[i + 1] != '\0')
					size += 1;
				size += 1;
			}
			else
			{
				if (i > 0 && input[i - 1] != ' ' && input[i - 1] != '\0' && !insideQuotes)
					size += 1;
				size += 1;
			}
			insideSingleQuotes = !insideSingleQuotes;
		}
		else
			size += 1;
		i++;
	}
	size += 1;
	return (size);
}

char *fix_quotes(char *input)
{
	int		size;
	int		insideQuotes = 0;
	int		insideSingleQuotes = 0;
	char	*output;
	int 	i;
	int 	j;

	size = count_len(input);
	insideQuotes = 0;
	insideSingleQuotes = 0;
	output = (char*)malloc(size);
	if (output == NULL)
    	return (NULL);
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\"' && !insideSingleQuotes)
		{
			if (insideQuotes)
			{
				if (input[i + 1] != ' ' && input[i + 1] != '\0')
				{
					output[j++] = '\"';
					output[j++] = ' ';
				}
				else
					output[j++] = '\"';
		}
		else
		{
			if (i > 0 && input[i - 1] != ' ' && output[j - 1] != ' ' && input[i - 1] != '\0' && !insideSingleQuotes) 
				output[j++] = ' ';
			output[j++] = '\"';
		}
		insideQuotes = !insideQuotes;
		}
		else if (input[i] == '\'' && !insideQuotes)
		{
			if (insideSingleQuotes)
			{
        if (input[i + 1] != ' ' && input[i + 1] != '\0')
        {
          output[j++] = '\'';
          output[j++] = ' ';
        }
        else
          output[j++] = '\'';
      }
      else
      {
        if (i > 0 && input[i - 1] != ' ' && output[j - 1] != ' ' && input[i - 1] != '\0' && !insideQuotes) 
          output[j++] = ' ';
        output[j++] = '\'';
      }
      insideSingleQuotes = !insideSingleQuotes;
    }
    else
      output[j++] = input[i];
    i++;
  }
  output[j] = '\0';     
  return output;
}

