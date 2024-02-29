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
	t_node *temp;
	int i;
	int j;

	temp = list->head;
	while (temp != NULL) 
	{
		i = 0;
		while (temp->arg[i])
		{
			j = 0;
			while (temp->arg[i][j])
			{
				if (temp->arg[i][j] == -32) 
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

int check_syntax(p_dblst *list)
{
	x_node *head = list->head;
	if (strcmp(head->str, "|") == 0 && head->next->type == STRING)
	{
		printf("bash: syntax error near unexpected token\n");
		return (1);
	}
	while(head)
	{
		if ((head->type == REDIN && head->next && head->next->type == PIPE) ||
			(head->type == REDOUT && head->next && head->next->type == PIPE) ||
			(head->type == APPEND && head->next && head->next->type == PIPE) ||
			(head->type == APPEND && head->next && head->next->type == REDOUT) ||
			(head->type == APPEND && head->next && head->next->type == APPEND) ||
			(head->type == HERDOC && head->next && head->next->type == PIPE) ||
			(head->type == HERDOC && head->next && head->next->type == HERDOC) ||
			(head->type == HERDOC && head->next && head->next->type == REDIN) ||
			(head->type == HERDOC && head->next && head->next->type == REDOUT) ||
			(head->type == HERDOC && head->next && head->next->type == APPEND) ||
			(head->type == PIPE && head->next && head->next->type == REDIN) ||
			(head->type == PIPE && head->next && head->next->type == REDOUT) ||
			(head->type == PIPE && head->next && head->next->type == APPEND) ||
			(head->type == PIPE && head->next && head->next->type == HERDOC) ||
			(head->type == PIPE && head->next && head->next->type == PIPE) ||
			(strcmp(head->str, "|") == 0 && head->next == NULL) ||
			(strcmp(head->str, ">>") == 0 && head->next == NULL) ||
			(strcmp(head->str, "<<") == 0 && head->next == NULL) ||
			(strcmp(head->str, ">") == 0 && head->next == NULL) ||
			(strcmp(head->str, "!") == 0 && head->next == NULL) ||
			(strcmp(head->str, "<") == 0 && head->next == NULL))
		{
			printf("bash: syntax error near unexpected token\n");
			return (1);
		}
		head = head->next;
	}
	return (0);
}

void add_redi_to_list(t_dblst *list, p_dblst *p_list)
{
	t_node *e_temp;
	x_node *p_temp;

	e_temp = list->head;
	p_temp = p_list->head;
	while (p_temp)
	{
		if (p_temp->next && (strcmp(p_temp->str, ">") == 0 || strcmp(p_temp->str, ">>") == 0))
		{
			e_temp->fd_out = p_temp->next->fd_out;
		}
		if (p_temp->next && (strcmp(p_temp->str, "<") == 0 || strcmp(p_temp->str, "<<") == 0))
		{
			e_temp->fd_in = p_temp->next->fd_in;
		}
		if (p_temp->next && (strcmp(p_temp->str, "|") == 0))
			e_temp = e_temp->next;
		p_temp = p_temp->next;
	}
}


void fix_e_line(const char *f_line, char *e_line) 
{
	const char *f_quote = f_line;
	char *e_quote = e_line;

	// Iterate over each pair of quotes in f_line and e_line
	while ((f_quote = strchr(f_quote, '"')) && (e_quote = strchr(e_quote, '"')))
	{
		// Check if there is no space before the quote in f_line
		if (*(f_quote - 1) != ' ') {
			// Check if there is a space before the quote in e_line
			if (*(e_quote - 1) == ' ') {
				// Remove the space before the quote in e_line
				memmove(e_quote - 1, e_quote, strlen(e_quote) + 1);
			}
		}

		// Check if there is no space after the quote in f_line
		if (*(f_quote + 1) != ' ' && *(f_quote + 1) != '\0') {
			// Check if there is a space after the quote in e_line
			if (*(e_quote + 1) == ' ') {
				// Remove the space after the quote in e_line
				memmove(e_quote + 1, e_quote + 2, strlen(e_quote + 1) + 1);
			}
		}
		// Move to the next quote in f_line and e_line
		f_quote++;
		e_quote++;
	}
}


void lexer(char *line, t_dblst *list)
{
	p_dblst p_list;
	if (!(fix_input(line))) // || inside quotes is not working
		return ;
	char *fixed_line = fix_line(line);
	if (!(check_quotes(fixed_line)))
		return ;
	// printf("%s\n", fixed_line);
	char *p_line = fix_quotes(fixed_line);
	p_list = tokenize_list(p_line);
	// print(&p_list);
	if (check_syntax(&p_list))
		return ;
	expand(&p_list);
	// print(&p_list);
	char *e_line = exec_line(&p_list);
	// fix_e_line(e_line, fixed_line);
	remove_quotes(&p_list);
	redirections(&p_list);
	// printf("-----------------\n");
	fix_e_line(fixed_line, e_line);
	remove_line_quotes(e_line);
	printf("fix e_line : %s\n", e_line);
	char **str = ft_split(e_line, '|');
	// int i = 0;
	// while (str[i])
	// printf("%s\n",str[i++]);
	////remove_spaces_inq(str);
	//i = 0;
	//while (str[i])
	//printf("%s\n",str[i++]);
	add_list(str, list);
	add_spaces_back(list);
	add_redi_to_list(list, &p_list);
	//print_list(list);

	//        FREE
	// free_slist(&p_list);
	// ft_free(str);
	// free(p_line);
	// free(fixed_line);
	// free(e_line);
	return ;
}


