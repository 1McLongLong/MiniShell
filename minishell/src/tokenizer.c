#include "header.h"

x_node *create_snode(char *data)
{
	x_node *new_node = malloc(sizeof(x_node));
	if (new_node == NULL)
		return NULL;
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->type = 0;
	new_node->str = strdup(data);
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}
/*x_node *add_to_slist(x_node *list, char *data)
{
	x_node *new_node = create_snode(data);
	if (new_node == NULL)
		return NULL;
	if (list == NULL)
		list = new_node;
	else
	{
		x_node *current = list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	return list;
}*/

void add_to_slist(p_dblst *list, char *data)
{
	x_node *new_node;

	new_node = create_snode(data);
	if (list->head == NULL)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

void	free_slist(p_dblst *list)
{
	x_node	*current;
	x_node	*next;

	current = list->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
}

void add_slist(char *str, p_dblst *list)
{
	int i = 0;
	char **split = token_split(str, ' ');
	while (split[i])
	{
		add_to_slist(list, split[i]);
		i++;
	}
	ft_free(split);
}

void remove_spaces(char *str)
{
	int i = 0;
	int inside_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			inside_quotes = !inside_quotes;
		if (inside_quotes && (str[i] == ' '))
		{
			str[i] *= -1;
		}
		i++;
	}
}

// void print(x_node *list)
// {
// 	x_node *temp;
//
// 	temp = list;
// 	while (temp)
// 	{
// 		// printf("%s ---------- %d\n", temp->str, temp->type);
// 		printf("%s ---------- in = %d | out = %d\n", temp->str, temp->fd_in, temp->fd_out);
// 		// printf("%s\n", temp->str);
// 		temp = temp->next; 
// 	}
// }

void print(p_dblst *list)
{
	x_node *temp;

	temp = list->head;
	// int i;
	while (temp)
	{
 		printf("%s ---------- %d\n", temp->str, temp->type);
 		// printf("%s ---------- in = %d | out = %d\n", temp->str, temp->fd_in, temp->fd_out);
		// printf("%s\n", temp->str);
		temp = temp->next; 
	}
}

void tokenize_my_list(p_dblst *list)
{
	x_node *head = list->head;
	head->type = COMMAND;
	head = head->next;
	while (head)
	{
		if (!(strcmp(head->str, "|")))
		{
			head->type = PIPE;
			if (head->next == NULL)
				break ;
			head->next->type = COMMAND;
		}
		else if (strstr(head->str, "-"))
		{
			head->type = ARG;
		}
		else if (!(strcmp(head->str, "<")))
		{
			head->type = REDIN;
			if (head->next == NULL)
				break ;
			head->next->type = INFILE;
		}
		else if (!(strcmp(head->str, ">")))
		{
			head->type = REDOUT;
			if (head->next == NULL)
				break ;
			head->next->type = OUTFILE;
		}
		else if (!(strcmp(head->str, ">>")))
		{
			head->type = APPEND;
				if (head->next == NULL)
				break ;
			head->next->type = DELIMITER;
		}	
		else if (!(strcmp(head->str, "<<")))
		{
			head->type = HERDOC;
			if (head->next == NULL)
				break ;
			head->next->type = DELIMITER;
		}
		else if (head->type == 0)
			head->type = STRING;
		head = head->next;
	}
}


p_dblst tokenize_list(char *str)
{
	p_dblst list;
	list.head = NULL;
	list.tail = NULL;
	remove_spaces(str);
	//printf("%s\n", str);
	add_slist(str, &list);
	tokenize_my_list(&list);
	// print(&list);
	return (list);
}
