#include "header.h"

void	delete_node(p_dblst **list)
{
	x_node	*current;
	x_node	*next;
	x_node	*prev;

	prev = NULL;
	current = (*list)->head;
	while (current)
	{
		if (strcmp(current->str, "\"\"") == 0)
		{
			next = current->next;
			free(current);
			if (prev)
				prev->next = next;
			else
				(*list)->head = next;
			if (next)
				next->prev = prev;
			if (next == NULL)
			{
				(*list)->head = NULL;
				return ;
			}
			current = next;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	remove_quotes(p_dblst *p_list)
{
	x_node	*head;
	char	*temp;

	if (p_list == NULL || p_list->head == NULL)
		return ;
	delete_node(&p_list);
	head = p_list->head;
	while (head)
	{
		if (head->str && (head->str[0] == '"' || head->str[0] == '\''))
		{
			temp = head->str;
			head->str = ft_substr(temp, 1, ft_strlen(temp) - 2);
			free(temp);
		}
		head = head->next;
	}
}

void	remove_line_quotes(char *str)
{
	t_index	index;
	int		inside_dquotes;
	int		inside_s_quotes;

	inside_dquotes = 0;
	inside_s_quotes = 0;
	memset(&index, 0, sizeof(index));
	while (str[index.i])
	{
		if (str[index.i] == '\"' && !inside_s_quotes)
		{
			inside_dquotes = !inside_dquotes;
			index.i++;
		}
		else if (str[index.i] == '\'' && !inside_dquotes)
		{
			inside_s_quotes = !inside_s_quotes;
			index.i++;
		}
		else if (inside_dquotes || inside_s_quotes)
			str[index.j++] = str[index.i++];
		else
			str[index.j++] = str[index.i++];
	}
	str[index.j] = '\0';
}









