/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:46:17 by touahman          #+#    #+#             */
/*   Updated: 2024/03/05 12:45:33 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

x_node	*create_snode(char *data)
{
	x_node	*new_node;

	new_node = malloc(sizeof(x_node));
	if (new_node == NULL)
		return (NULL);
	new_node->fd_in = 0;
	new_node->fd_out = 1;
	new_node->type = 0;
	new_node->str = ft_strdup(data);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	add_to_slist(p_dblst *list, char *data)
{
	x_node	*new_node;

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

void	add_slist(char *str, p_dblst *list)
{
	char	**split;
	int		i;

	i = 0;
	split = token_split(str, ' ');
	while (split[i])
	{
		add_to_slist(list, split[i]);
		i++;
	}
	ft_free(split);
}
