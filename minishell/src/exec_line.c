/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:07:10 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 12:07:11 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*exec_line(p_dblst *list)
{
	x_node	*head;
	t_index	index;

	memset(&index, 0, sizeof(index));
	if (list->head == NULL)
		return (NULL);
	head = list->head;
	while (head != NULL)
	{
		index.len += strlen(head->str) + 1;
		head = head->next;
	}
	index.result = (char *)malloc(index.len + 1);
	if (index.result == NULL)
		return (NULL);
	head = list->head;
	while (head != NULL)
	{
		strcpy(index.result + index.i, head->str);
		index.i += strlen(head->str);
		index.result[index.i++] = ' ';
		head = head->next;
	}
	index.result[index.len - 1] = '\0';
	return (index.result);
}

static void	e_quotes(char *f_line, char *e_line, char quote_type)
{
	char	*f_quote;
	char	*e_quote;

	f_quote = f_line;
	e_quote = e_line;
	f_quote = strchr(f_quote, quote_type);
	e_quote = strchr(e_quote, quote_type);
	while (f_quote && e_quote)
	{
		if (f_quote != f_line && *(f_quote - 1) != ' ')
		{
			if (e_quote != e_line && *(e_quote - 1) == ' ')
				memmove(e_quote - 1, e_quote, strlen(e_quote) + 1);
		}
		if (*(f_quote + 1) != ' ' && *(f_quote + 1) != '\0')
		{
			if (*(e_quote + 1) == ' ' && *(e_quote + 1) != '\0')
				memmove(e_quote + 1, e_quote + 2, strlen(e_quote + 1) + 1);
		}
		f_quote = strchr(f_quote + 1, quote_type);
		e_quote = strchr(e_quote + 1, quote_type);
	}
}

void	fix_e_line(char *f_line, char *e_line)
{
	e_quotes(f_line, e_line, '"');
	e_quotes(f_line, e_line, '\'');
}
