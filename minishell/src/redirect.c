/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:29:55 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 19:29:56 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_opened_fd(p_dblst *list, x_node *last_fnode, int flag)
{
	x_node	*temp;

	temp = list->head;
	while (temp != last_fnode)
		temp = temp->next;
	while (temp)
	{
		if (flag == 1 && temp->fd_out != 1)
		{
			close(temp->fd_out);
			temp->fd_out = -1;
		}
		else if (flag == 0 && temp->fd_in != 0)
		{
			close(temp->fd_in);
			temp->fd_in = -1;
		}
		if (temp->prev && strcmp(temp->prev->str, "|") == 0)
			break ;
		temp = temp->prev;
	}
}

void	redirect_output(p_dblst *list, x_node *temp)
{
	int	fd;

	check_opened_fd(list, temp, 1);
	fd = open(temp->next->str, O_CREAT | O_RDWR);
	if (fd == -1)
		perror("ERROR");
	temp->next->fd_out = fd;
}

void	redirect_input(p_dblst *list, x_node *temp)
{
	int	fd;

	check_opened_fd(list, temp, 0);
	fd = open(temp->next->str, O_CREAT | O_RDONLY);
	if (fd == -1)
		perror("ERROR");
	temp->next->fd_in = fd;
}

void	redirect_append(p_dblst *list, x_node *temp)
{
	int	fd;

	check_opened_fd(list, temp, 1);
	fd = open(temp->next->str, O_CREAT | O_RDWR | O_TRUNC);
	if (fd == -1)
		perror("ERROR");
	temp->next->fd_out = fd;
}

void	redirections(p_dblst *list)
{
	x_node	*temp;

	temp = list->head;
	while (temp)
	{
		if (strcmp(temp->str, ">") == 0 && temp->next)
			redirect_output(list, temp);
		else if (strcmp(temp->str, "<") == 0 && temp->next)
			redirect_input(list, temp);
		else if (strcmp(temp->str, ">>") == 0 && temp->next)
			redirect_append(list, temp);
		else if (strcmp(temp->str, "<<") == 0 && temp->next)
		{
			check_opened_fd(list, temp, 0);
			heredoc(temp);
		}
		temp = temp->next;
	}
}
