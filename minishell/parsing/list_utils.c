/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:47:56 by touahman          #+#    #+#             */
/*   Updated: 2024/03/05 12:46:32 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_node	*create_node(char *data)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return (NULL);
	new_node->arg = ft_split(data, ' ');
	new_node->cmd = NULL;
	if (new_node->arg[0])
		new_node->cmd = ft_strdup(new_node->arg[0]);
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

void	free_list(t_dblst *list)
{
	t_node	*current;
	t_node	*next;

	current = list->head;
	while (current != NULL)
	{
		next = current->next;
		ft_free(current->arg);
		free(current->cmd);
		free(current);
		current = next;
	}
	list->head = NULL;
	list->tail = NULL;
}


void	print_list(t_dblst *list)
{
	t_node	*temp;
	int		i;

	temp = list->head;
	while (temp)
	{
		// printf("%s  -------- %d\n", temp->cmd, temp->type);
		i = 0;
		while (temp->arg[i])
			printf("%s ", temp->arg[i++]);
		// printf("\nin = %d | out = %d", temp->fd_in, temp->fd_out);
		printf("\n");
		temp = temp->next; 
	}
}


void	add_list(char **str, t_dblst *list)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		add_to_list(list, str[i]);
		i++;
	}
}
