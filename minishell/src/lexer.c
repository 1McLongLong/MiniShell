#include "header.h"

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
	{
		free(fixed_line);
		return ;
	}
	 // printf("fixed_line: %s\n", fixed_line);
	char *p_line = fix_quotes(fixed_line);
	// printf("p_line: %s\n", p_line);
	p_list = tokenize_list(p_line);
	// print(&p_list);
	if (check_syntax(&p_list))
	{
		free_slist(&p_list);
		free(p_line);
		free(fixed_line);
		return ;
	}
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
	// print_list(list);

	//        FREE
	free_slist(&p_list);
	ft_free(str);
	free(p_line);
	free(fixed_line);
	free(e_line);
	return ;
}
