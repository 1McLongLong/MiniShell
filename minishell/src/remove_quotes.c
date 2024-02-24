#include "header.h"

void delete_node(x_node **list)
{
	x_node *current = *list;
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
				*list = next;  // Update list if the first node is being deleted
			current = next;
		} 
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void remove_quotes(x_node *p_list)
{
	x_node *head = p_list;
	delete_node(&p_list);
	while (head)
	{
		if (head->str[0] == '"' || head->str[0] == '\'')
		{
			char *temp = head->str;
			head->str = ft_substr(temp, 1, ft_strlen(temp) - 2);
			free(temp);
		}
		head = head->next;
	}
}
