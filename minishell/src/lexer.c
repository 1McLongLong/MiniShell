
#include "header.h"


int fix_input(char *line)
{
	epur_str(line);
	if (line[0] == '#')
		return (0);
	int i = 0;
	int inside_quotes = 0;
	while (line[i])
	{
		if (line[i] == '"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes && line[i] == '|' && line[i + 1] == '|')
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

void check_syntax(x_node *list)
{
	x_node *head = list;
	while(head)
	{
		if ((head->type == REDIN && head->next && head->next->type == PIPE) ||
			(head->type == REDOUT && head->next && head->next->type == PIPE) ||
			(head->type == APPEND && head->next && head->next->type == PIPE) ||
			(head->type == HERDOC && head->next && head->next->type == PIPE) ||
			(head->type == PIPE && head->next && head->next->type == REDIN) ||
			(head->type == PIPE && head->next && head->next->type == REDOUT) ||
			(head->type == PIPE && head->next && head->next->type == APPEND) ||
			(head->type == PIPE && head->next && head->next->type == HERDOC) ||
			(head->type == PIPE && head->next && head->next->type == PIPE) ||
			(head->type == PIPE && head->next == NULL) ||
			(head->type == REDIN && head->next == NULL) ||
			(head->type == REDOUT && head->next == NULL) ||
			(head->type == APPEND && head->next == NULL) ||
			(head->type == HERDOC && head->next == NULL))
		{
			printf("bash: syntax error near unexpected token\n");
			break ;
		}
		head = head->next;
	}
}

void lexer(char *line, t_dblst *list)
{
	(void)list;
	x_node *p_list;
	if (!(fix_input(line))) // || inside quotes is not working
		return ;
	char *fixed_line = fix_line(line);
	if (!(check_quotes(fixed_line)))
		return ;
	//printf("%s\n", fixed_line);
	char *p_line = fix_quotes(fixed_line);
	// printf("%s\n", p_line);
	p_list = tokenize_list(p_line);
	// print(p_list);
	check_syntax(p_list);
  // printf("------------\n");
	expand(p_list);
	remove_quotes(p_list);
	redirections(p_list);
	//print(p_list);
	////char **str = ft_split(fixed_line, '|');
	//int i = 0;
	//while (str[i])
	//printf("%s\n",str[i++]);
	////remove_spaces_inq(str);
	//i = 0;
	//while (str[i])
	//printf("%s\n",str[i++]);
	////add_list(str, list);
	////add_spaces_back(list);
	////print_list(list);
	//ft_free(str);
	free(fixed_line);
	return ;
}


