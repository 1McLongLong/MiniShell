#include "header.h"


int fix_input(char *line)
{
	epur_str(line);
	if (line[0] == '#')
		return (0);
	return (1);
}

void add_list(char **str, t_dblst *list)
{
	int i = 0;
	while (str[i] != NULL)
	{
		add_to_list(list, str[i]);
		i++;
	}
}

void tokenize_my_list(t_dblst *list)
{
	t_node *head = list->head;
	while (head)
	{
		if (!(strcmp(head->data, "echo")))
		{
			head->type = TOKEN_COMMAND;
			head = head->next;
			while (head)
			{
				head->type = TOKEN_STRING;
				head = head->next;
			}
		}
	}

	print_list(list);
}

int lexer(char *line, t_dblst *list)
{
	if (!(fix_input(line)))
		return (0);
	char **str = ft_split(line, ' ');
	add_list(str, list);
	tokenize_my_list(list);
	return (1);
}
