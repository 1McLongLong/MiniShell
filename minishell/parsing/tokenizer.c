/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:28:04 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 18:28:22 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	tokenize_my_list(p_dblst *list)
{
	x_node	*head;

	head = list->head;
	mark_pipes(head);
	mark_redirection_input(head);
	mark_redirection_output(head);
	mark_heredoc(head);
	mark_arguments(head);
}

p_dblst	tokenize_list(char *str)
{
	p_dblst	list;

	list.head = NULL;
	list.tail = NULL;
	remove_spaces(str);
	add_slist(str, &list);
	tokenize_my_list(&list);
	return (list);
}
