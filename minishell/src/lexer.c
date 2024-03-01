#include "header.h"

int	fix_input(char *line)
{
	int	i;
	int	inside_quotes;

	inside_quotes = 0;
	i = 0;
	if (line[0] == '#')
		return (0);
	epur_str(line);
	while (line[i])
	{
		if (line[i] == '"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes && line[i] == '|' && line[i + 1] == '|')
			return (printf("Syntax error!\n"), 0);
		else if (line[i] == '>' && line[i + 1] == ' ' && line[i + 2] == '>')
			return (printf("Syntax error!\n"), 0);
		else if (line[i] == '<' && line[i + 1] == ' ' && line[i + 2] == '<')
			return (printf("Syntax error!\n"), 0);
		i++;
	}
	return (1);
}

char	*fix_line(char *str)
{
	t_index	index;
	int		len;
	int		inquotes;
	char	*result;

	len = str_len(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	inquotes = 0;
	memset(&index, 0, sizeof(t_index));
	while (index.i < len && index.j < len)
	{
		if (str[index.i] == '"')
		{
			inquotes = !inquotes;
			result[index.j++] = str[index.i];
		}
		else if (!inquotes && (str[index.i] == '|' || (str[index.i] == '>') || (str[index.i] == '<')))
		{
			if (index.i > 0 && str[index.i - 1] != ' ')
				result[index.j++] = ' ';
			result[index.j++] = str[index.i];
			if (index.i < len - 1 && str[index.i + 1] != ' ')
				result[index.j++] = ' ';
		}
		else
			result[index.j++] = str[index.i];
		index.i++;
	}
	result[index.j] = '\0';
	fix_it_again(result);
	return (result);
}

int	check_quotes(char *input)
{
	int	singlequotes;
	int	doublequotes;
	int	escaped;
	int	i;

	singlequotes = 0;
	doublequotes = 0;
	escaped = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\\' && !escaped)
			escaped = 1;
		else if (input[i] == '\'' && !escaped && doublequotes % 2 == 0) 
			singlequotes++;
		else if (input[i] == '\"' && !escaped && singlequotes % 2 == 0) 
			doublequotes++;
		if (input[i] == '\\' && escaped)
			escaped = 0;
		i++;
	}
	if (singlequotes % 2 != 0 || doublequotes % 2 != 0) 
		return (printf("Syntax error!\n"), 0);
	return (1);
}

void	remove_spaces_inq(char **str)
{
	int	i;
	int	inside_quotes;
	int	j;

	i = 0;
	inside_quotes = 0;
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

void	add_spaces_back(t_dblst *list)
{
	t_node	*temp;
	int		i;
	int		j;

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

int	check_syntax(p_dblst *list)
{
	x_node *head;

	head = list->head;
	if (strcmp(head->str, "|") == 0 && head->next->type == STRING)
		return (printf("bash: syntax error near unexpected token\n"), 1);
	while (head)
	{
		if ((head->type == REDIN && head->next && head->next->type == PIPE)
			|| (head->type == REDOUT && head->next && head->next->type == PIPE)
			|| (head->type == APPEND && head->next && head->next->type == PIPE)
			|| (head->type == APPEND && head->next && head->next->type == REDOUT)
			|| (head->type == APPEND && head->next && head->next->type == APPEND)
			|| (head->type == HERDOC && head->next && head->next->type == PIPE) 
			|| (head->type == HERDOC && head->next && head->next->type == HERDOC)
			|| (head->type == HERDOC && head->next && head->next->type == REDIN)
			|| (head->type == HERDOC && head->next && head->next->type == REDOUT)
			|| (head->type == HERDOC && head->next && head->next->type == APPEND)
			|| (head->type == PIPE && head->next && head->next->type == REDIN)
			|| (head->type == PIPE && head->next && head->next->type == REDOUT)
			|| (head->type == PIPE && head->next && head->next->type == APPEND)
			|| (head->type == PIPE && head->next && head->next->type == HERDOC)
			|| (head->type == PIPE && head->next && head->next->type == PIPE)
			|| (strcmp(head->str, "|") == 0 && head->next == NULL)
			|| (strcmp(head->str, ">>") == 0 && head->next == NULL)
			|| (strcmp(head->str, "<<") == 0 && head->next == NULL)
			|| (strcmp(head->str, ">") == 0 && head->next == NULL)
			|| (strcmp(head->str, "!") == 0 && head->next == NULL)
			|| (strcmp(head->str, "<") == 0 && head->next == NULL))
			return (printf("bash: syntax error near unexpected token\n"), 1);
		head = head->next;
	}
	return (0);
}

void	add_redi_to_list(t_dblst *list, p_dblst *p_list)
{
	t_node	*e_temp;
	x_node	*p_temp;

	e_temp = list->head;
	p_temp = p_list->head;
	while (p_temp)
	{
		if (p_temp->next && (strcmp(p_temp->str, ">") == 0
			|| strcmp(p_temp->str, ">>") == 0))
		{
			e_temp->fd_out = p_temp->next->fd_out;
		}
		if (p_temp->next && (strcmp(p_temp->str, "<") == 0
			|| strcmp(p_temp->str, "<<") == 0))
		{
			e_temp->fd_in = p_temp->next->fd_in;
		}
		if (p_temp->next && (strcmp(p_temp->str, "|") == 0))
			e_temp = e_temp->next;
		p_temp = p_temp->next;
	}
}


void	lexer(char *line, t_dblst *list)
{
	p_dblst	p_list;
	if (!(fix_input(line))) // || inside quotes is not working
		return ;
	char *fixed_line = fix_line(line);
	if (!(check_quotes(fixed_line)))
		return ;
	 // printf("fixed_line: %s\n", fixed_line);
	char *p_line = fix_quotes(fixed_line);
	p_list = tokenize_list(p_line);
	// print(&p_list);
	if (check_syntax(&p_list))
		return ;
	expand(&p_list);
	// print(&p_list);
	char *e_line = exec_line(&p_list);
	// printf("e_line : %s\n", e_line);
	remove_quotes(&p_list);
	redirections(&p_list);
	// printf("-----------------\n");
	fix_e_line(fixed_line, e_line);
	remove_line_quotes(e_line);
	// printf("fix e_line : %s\n", e_line);
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
	print_list(list);

	//        FREE
	free_slist(&p_list);
	ft_free(str);
	free(p_line);
	free(fixed_line);
	free(e_line);
	return ;
}


