#include "header.h"

void delete_node(p_dblst **list)
{
	x_node *current = (*list)->head;
	x_node *prev = NULL;
	x_node *next;

	while (current) 
	{
		if (strcmp(current->str, "\"\"") == 0)
		{
			next = current->next;
			free(current);
			if (prev)
				prev->next = next;
			else
				(*list)->head = next;  // Update list if the first node is being deleted
			if (next)
				next->prev = prev;
			if (next == NULL)
			{
				(*list)->head = NULL;
				return;
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

void remove_quotes(p_dblst *p_list)
{
	if (p_list == NULL || p_list->head == NULL)
		return ;
	delete_node(&p_list);
	x_node *head = p_list->head;
	while (head)
	{
		if (head->str && (head->str[0] == '"' || head->str[0] == '\''))
		{
			char *temp = head->str;
			head->str = ft_substr(temp, 1, ft_strlen(temp) - 2);
			free(temp);
		}
		head = head->next;
	}
}
