/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 15:10:52 by touahman          #+#    #+#             */
/*   Updated: 2024/03/05 16:22:33 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	fix_input(char *line)
{
	int	i;
	int	inside_quotes;

	inside_quotes = 0;
	i = 0;
	if (line[0] == '#')
		return (0);
	epur_str(line);
	while (line[i])
	{
		if (line[i] == '"')
			inside_quotes = !inside_quotes;
		if (!inside_quotes && line[i] == '|' && line[i + 1] == '|')
			return (printf("Syntax error!\n"), 0);
		else if (!inside_quotes && line[i] == '|' && line[i + 1] == '\0')
			return (printf("Syntax error!\n"), 0);
		else if (line[i] == '>' && line[i + 1] == ' ' && line[i + 2] == '>')
			return (printf("Syntax error!\n"), 0);
		else if (line[i] == '<' && line[i + 1] == ' ' && line[i + 2] == '<')
			return (printf("Syntax error!\n"), 0);
		i++;
	}
	return (1);
}

int	check_quotes(char *input)
{
	int	singlequotes;
	int	doublequotes;
	int	escaped;
	int	i;

	singlequotes = 0;
	doublequotes = 0;
	escaped = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\\' && !escaped)
			escaped = 1;
		else if (input[i] == '\'' && !escaped && doublequotes % 2 == 0)
			singlequotes++;
		else if (input[i] == '\"' && !escaped && singlequotes % 2 == 0)
			doublequotes++;
		if (input[i] == '\\' && escaped)
			escaped = 0;
		i++;
	}
	if (singlequotes % 2 != 0 || doublequotes % 2 != 0)
		return (printf("Syntax error!\n"), 0);
	return (1);
}

static int	has_invalid_sequence(x_node *node)
{
	if ((node->type == REDIN && node->next && node->next->type == PIPE)
		|| (node->type == REDOUT && node->next && node->next->type == PIPE)
		|| (node->type == APPEND && node->next && node->next->type == PIPE)
		|| (node->type == APPEND && node->next && node->next->type == REDOUT)
		|| (node->type == APPEND && node->next && node->next->type == APPEND)
		|| (node->type == HERDOC && node->next && node->next->type == PIPE)
		|| (node->type == HERDOC && node->next && node->next->type == HERDOC)
		|| (node->type == HERDOC && node->next && node->next->type == REDIN)
		|| (node->type == HERDOC && node->next && node->next->type == REDOUT)
		|| (node->type == HERDOC && node->next && node->next->type == APPEND)
		|| (node->type == PIPE && node->next && node->next->type == REDIN)
		|| (node->type == PIPE && node->next && node->next->type == REDOUT)
		|| (node->type == PIPE && node->next && node->next->type == APPEND)
		|| (node->type == PIPE && node->next && node->next->type == HERDOC)
		|| (node->type == PIPE && node->next && node->next->type == PIPE))
	{
		return (1);
	}
	return (0);
}

static int	has_unexpected_token(x_node *node)
{
	if (strcmp(node->str, "|") == 0 || strcmp(node->str, ">>") == 0
		|| strcmp(node->str, "<<") == 0 || strcmp(node->str, ">") == 0
		|| strcmp(node->str, "!") == 0 || strcmp(node->str, "<") == 0)
	{
		if (node->next == NULL)
			return (1);
	}
	return (0);
}

int	check_syntax(p_dblst *list)
{
	x_node	*head;

	head = list->head;
	if (strcmp(head->str, "|") == 0 && head->next->type == STRING)
		return (printf("bash: syntax error near unexpected token\n"), 1);
	while (head)
	{
		if (has_invalid_sequence(head) || has_unexpected_token(head))
			return (printf("bash: syntax error near unexpected token\n"), 1);
		head = head->next;
	}
	return (0);
}
