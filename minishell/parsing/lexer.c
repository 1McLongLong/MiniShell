#include "header.h"

char	*fix_line(char *str)
{
	t_index	index;
	int		inquotes;
	char	*result;

	memset(&index, 0, sizeof(t_index));
	index.len = str_len(str);
	result = malloc(sizeof(char) * (index.len + 1));
	if (!result)
		return (NULL);
	inquotes = 0;
	while (index.i < index.len && index.j < index.len)
	{
		if (str[index.i] == '"' || str[index.i] == '\'')
		{
			inquotes = !inquotes;
			result[index.j++] = str[index.i];
		}
		else if (!inquotes && ((str[index.i] == '|') || (str[index.i] == '>')
				|| (str[index.i] == '<')))
		{
			if (index.i > 0 && str[index.i - 1] != ' ')
				result[index.j++] = ' ';
			result[index.j++] = str[index.i];
			if (index.i < index.len - 1 && str[index.i + 1] != ' ')
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
	char *fixed_line;
	char *p_line;
	char	*e_line;
	char **str;

	if (!(fix_input(line)))
		return ;
	fixed_line = fix_line(line);
	if (!(check_quotes(fixed_line)))
	{
		return (free(fixed_line));
	}
	// printf("fixed_line: %s\n", fixed_line);
	p_line = fix_quotes(fixed_line);
	// printf("p_line: %s\n", p_line);
	p_list = tokenize_list(p_line);
	// print(&p_list);
	if (check_syntax(&p_list))
		return (free_slist(&p_list), free(p_line), free(fixed_line));
	expand(&p_list);
	// print(&p_list);
	e_line = exec_line(&p_list);
	// printf("e_line : %s\n", e_line);
	remove_quotes(&p_list);
	redirections(&p_list);
	// printf("-----------------\n");
	fix_e_line(fixed_line, e_line);
	remove_line_quotes(e_line);
	// printf("fix e_ine : %s\n", e_line);
	str = ft_split(e_line, '|');
	// int i = 0;
	// while (str[i])
	// printf("%s\n",str[i++]);
	add_list(str, list);
	add_spaces_back(list);
	add_redi_to_list(list, &p_list);
	// print_list(list);

	//        FREE
	// free_slist(&p_list);
	// ft_free(str);
	// free(p_line);
	// free(fixed_line);
	// free(e_line);
	return (free_slist(&p_list), ft_free(str), free(p_line),
		free(fixed_line), free(e_line));
}