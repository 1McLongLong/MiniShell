#include "header.h"

e_node *create_enode(char *data)
{
	e_node *new_node = malloc(sizeof(e_node));
	if (new_node == NULL)
		return NULL;
	new_node->str = strdup(data);
	new_node->next = NULL;
	return new_node;
}

void add_env_list(e_node **list, char *data)
{
	e_node *new_node = create_enode(data);
	if (new_node == NULL)
		return ;
	if (*list == NULL)
		*list = new_node;
	else
	{
		e_node *current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}
void print_env(e_node *list)
{
	e_node *temp;

	temp = list;
	while (temp)
	{
		printf("%s\n", temp->str);
		temp = temp->next; 
	}
}

void free_envlist(e_node *list)
{
	e_node *temp;
	while (list) 
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp);
	}
}
void get_env(e_node **env_list, char **env)
{
	int i = 0;
	while (env[i])
	{
		add_env_list(env_list, env[i]);
		i++;
	}
	//print_env(*env_list);
}

