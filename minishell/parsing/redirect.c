/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 19:29:55 by touahman          #+#    #+#             */
/*   Updated: 2024/03/05 21:31:04 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	check_opened_fd(t_plist *list, t_pnode *last_fnode, int flag)
{
	t_pnode	*temp;

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

int	redirect_output(t_plist *list, t_pnode *temp)
{
	int	fd;

	check_opened_fd(list, temp, 1);
	fd = open(temp->next->str, O_CREAT | O_RDWR);
	if (fd == -1)
		return (perror("ERROR"), -1);
	temp->next->fd_out = fd;
	return (0);
}

int	redirect_input(t_plist *list, t_pnode *temp)
{
	int	fd;

	check_opened_fd(list, temp, 0);
	fd = open(temp->next->str, O_RDONLY);
	if (fd == -1)
		return (perror("ERROR"), -1);
	temp->next->fd_in = fd;
	return (0);
}

int	redirect_append(t_plist *list, t_pnode *temp)
{
	int	fd;

	check_opened_fd(list, temp, 1);
	fd = open(temp->next->str, O_CREAT | O_RDWR | O_TRUNC);
	if (fd == -1)
		return (perror("ERROR"), -1);
	temp->next->fd_out = fd;
	return (0);
}

void	redirections(t_plist *list)
{
	t_pnode	*temp;
	int		i;

	temp = list->head;
	while (temp)
	{
		i = 0;
		if (strcmp(temp->str, ">") == 0 && temp->next)
			i = redirect_output(list, temp);
		else if (strcmp(temp->str, "<") == 0 && temp->next)
			i = redirect_input(list, temp);
		else if (strcmp(temp->str, ">>") == 0 && temp->next)
			i = redirect_append(list, temp);
		else if (strcmp(temp->str, "<<") == 0 && temp->next)
		{
			check_opened_fd(list, temp, 0);
			heredoc(temp);
		}
		if (i == -1)
			while (temp && strcmp(temp->str, "|"))
				temp = temp->next;
		else
			temp = temp->next;
	}
}
