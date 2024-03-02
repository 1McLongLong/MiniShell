/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:48:19 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 20:10:25 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	delete_node_from_list(p_dblst **list, x_node *node)
{
	if (node == NULL || *list == NULL || (*list)->head == NULL)
		return ;
	if (node == (*list)->head)
		(*list)->head = node->next;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	free(node);
}

void	delete_node(p_dblst **list)
{
	x_node	*current;
	x_node	*next;

	current = (*list)->head;
	while (current != NULL)
	{
		next = current->next;
		if (strcmp(current->str, "\"\"") == 0)
		{
			delete_node_from_list(list, current);
		}
		current = next;
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
