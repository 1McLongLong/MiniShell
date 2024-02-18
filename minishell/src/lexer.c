#include "header.h"


int fix_input(char *line)
{
	epur_str(line);
	if (line[0] == '#')
		return (0);
	int i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|')
		{
			printf("Syntax error!\n");
			return (0);
		}
		else if (line[i] == '>' && line[i + 1] == ' ' && line[i + 2] == '>')
		{
			printf("Syntax error!\n");
			return (0);
		}
		else if (line[i] == '<' && line[i + 1] == ' ' && line[i + 2] == '<')
		{
			printf("Syntax error!\n");
			return (0);
		}
		i++;
	}
	return (1);
}

char *fix_line(char *str)
{ 
	int len = str_len(str);
	char *result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	int j = 0;
	int inquotes = 0;

	int i = 0;
	while (i < len && j < len) 
	{
		if (str[i] == '"')
		{
			inquotes = !inquotes;
			result[j++] = str[i];
		}
		else if (!inquotes && (str[i] == '|' || (str[i] == '>') || (str[i] == '<'))) 
		{
			if (i > 0 && str[i - 1] != ' ')
			{
				result[j++] = ' '; 
			}
			result[j++] = str[i];
			if (i < len - 1 && str[i + 1] != ' ') 
			{
				result[j++] = ' '; 
			}
		} 
		else 
		{
			result[j++] = str[i];	
		}
		i++;
	}
	result[j] = '\0';
	fix_it_again(result);
	return (result); 
}

void tokenize_my_list(t_dblst *list)
{
	t_node *head = list->head;
	while (head)
	{
		int i = 0;
		while(head->arg[i])
		{
			if (strstr(head->arg[i], "-"))
			{
				head->type = TOKEN_ARG;
			}
			else if (!(strcmp(head->arg[i], "<")))
			{
				head->type = TOKEN_INFILE;
				head->arg[i + 1] = ;
			}
			else if (!(strcmp(head->arg[i], ">")))
			{
				head->type = TOKEN_OUTFILE;
			}
			else if (!(strcmp(head->arg[i], ">>")))
			{
				head->type = TOKEN_DGREAT;
			}	
			else if (!(strcmp(head->arg[i], "<<")))
			{
				head->type = TOKEN_DLESS;
			}
			else if (!(strcmp(head->arg[i], "&")))
			{
				head->type = TOKEN_AMPERSAND;
			}
			else
				head->type = TOKEN_STRING;
			i++;
		}
		head = head->next;
	}
}


int check_quotes(char *input) 
{
	int singleQuotes = 0;
	int doubleQuotes = 0;
	int escaped = 0;

	for (int i = 0; input[i] != '\0'; i++) 
	{
		if (input[i] == '\\' && !escaped)
		{
			// If the backslash is not escaped, set the escaped flag
			escaped = 1;
		}
		else if (input[i] == '\'' && !escaped && doubleQuotes % 2 == 0) 
		{
			// Single quote outside double quotes
			singleQuotes++;
		}
		else if (input[i] == '\"' && !escaped && singleQuotes % 2 == 0) 
		{
			// Double quote outside single quotes
			doubleQuotes++;
		}
		// Reset escaped flag if the current character is not a backslashi 
		if (input[i] == '\\' && escaped)
			escaped = 0;
	}
	// Check if the total count of quotes is even
	if (singleQuotes % 2 != 0 || doubleQuotes % 2 != 0) 
	{
		printf("Syntax error!\n");
		return 0;
	}
	return 1;
}

/*
void check_syntax(char *str)
{
	(void)str;
}*/

void remove_spaces_inq(char **str)
{
	int i = 0;
	int inside_quotes = 0;
	int j;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '"')
				inside_quotes = !inside_quotes;
			if (inside_quotes && (str[i][j] == ' '))
			{
				str[i][j] *= -1;
			}
			j++;
		}
		i++;
	}
}

void add_spaces_back(t_dblst *list) 
{
	t_node *temp = list->head;
	int inside_quotes = 0;
	int i;
	int j;
	while (temp != NULL) 
	{
		i = 0;
		while (temp->arg[i])
		{
			j = 0;
			while (temp->arg[i][j])
			{
				if (temp->arg[i][j] == '"')
					inside_quotes = !inside_quotes;
				if (inside_quotes && temp->arg[i][j] == -32) 
				{
					temp->arg[i][j] *= -1;
				}
				j++;
			}
			i++;
		}
		temp = temp->next;
	}
}


void lexer(char *line, t_dblst *list)
{
	(void)list;
	if (!(fix_input(line))) // || inside quotes is not working
		return ;
	char *fixed_line = fix_line(line);
	if (!(check_quotes(fixed_line)))
		return ;
	//if (!(check_syntax(fixed_line)))
	//return ;
	//printf("%s\n", fixed_line);
	char **str = ft_split(fixed_line, '|');
	tokenize_my_list(fixed_line);
	//int i = 0;
	//while (str[i])
	//printf("%s\n",str[i++]);
	remove_spaces_inq(str);
	//i = 0;
	//while (str[i])
	//printf("%s\n",str[i++]);
	//char **test = ft_split(str[i], ' ');
	//i = 0;
	//while (test[i])
	//printf("%s\n",test[i++]);
	add_list(str, list);
	add_spaces_back(list);
	print_list(list);
	//ft_free(str);
	free(fixed_line);
	return ;
}


