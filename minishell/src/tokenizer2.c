/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 18:27:45 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 18:27:49 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	mark_pipes(x_node *head)
{
	while (head)
	{
		if (!(strcmp(head->str, "|")))
		{
			head->type = PIPE;
			if (head->next == NULL)
				break ;
			head->next->type = COMMAND;
		}
		head = head->next;
	}
}

void	mark_redirection_input(x_node *head)
{
	while (head)
	{
		if (!(strcmp(head->str, "<")))
		{
			head->type = REDIN;
			if (head->next == NULL)
				break ;
			head->next->type = INFILE;
		}
		head = head->next;
	}
}

void	mark_redirection_output(x_node *head)
{
	while (head)
	{
		if (!(strcmp(head->str, ">")))
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
		head = head->next;
	}
}

void	mark_heredoc(x_node *head)
{
	while (head)
	{
		if (!(strcmp(head->str, "<<")))
		{
			head->type = HERDOC;
			if (head->next == NULL)
				break ;
			head->next->type = DELIMITER;
		}
		head = head->next;
	}
}

void	mark_arguments(x_node *head)
{
	while (head)
	{
		if (strstr(head->str, "-"))
		{
			head->type = ARG;
		}
		else if (head->type == 0)
			head->type = STRING;
		head = head->next;
	}
}
