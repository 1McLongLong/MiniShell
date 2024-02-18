#include "header.h"

t_node	*create_node(char *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->arg = ft_split(data, ' ');
	new_node->cmd = strdup(new_node->arg[0]);
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_to_list(t_dblst *list, char *data)
{
	t_node	*new_node;

	new_node = create_node(data);
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

int	ft_lstsize(t_dblst *lst)
{
	t_node	*temp;
	int		size;

	temp = lst->head;
	size = 0;
	while (temp != NULL)
	{
		size++;
		temp = temp->next;
	}
	return (size);
}

void	free_list(t_dblst *list)
{
	t_node	*current;
	t_node	*next;

	current = list->head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
}

void print_list(t_dblst *list)
{
	t_node *temp;

	temp = list->head;
	int i;
	while (temp)
	{
		//printf("%s  -------- %d\n", temp->cmd, temp->type);
		i = 0;
		while (temp->arg[i])
			printf("%s ", temp->arg[i++]);
		//printf(" | %s", temp->cmd);
		printf("\n");
		temp = temp->next; 
	}
}

void add_list(char **str, t_dblst *list)
{
	int i = 0;
	while (str[i])
	{
		add_to_list(list,	str[i]);
		i++;
	}
}



