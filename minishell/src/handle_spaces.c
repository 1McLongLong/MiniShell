/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:37:13 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 13:41:13 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	remove_spaces_inq(char **str)
{
	int	i;
	int	inside_quotes;
	int	j;

	i = 0;
	inside_quotes = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '"')
				inside_quotes = !inside_quotes;
			if (inside_quotes && (str[i][j] == ' '))
			{
				str[i][j] *= -1;
			}
			j++;
		}
		i++;
	}
}

void	add_spaces_back(t_dblst *list)
{
	t_node	*temp;
	int		i;
	int		j;

	temp = list->head;
	while (temp != NULL)
	{
		i = 0;
		while (temp->arg[i])
		{
			j = 0;
			while (temp->arg[i][j])
			{
				if (temp->arg[i][j] == -32)
				{
					temp->arg[i][j] *= -1;
				}
				j++;
			}
			i++;
		}
		temp = temp->next;
	}
}

void	remove_spaces(char *str)
{
	int	i;
	int	inside_quotes;

	i = 0;
	inside_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			inside_quotes = !inside_quotes;
		if (inside_quotes && (str[i] == ' '))
		{
			str[i] *= -1;
		}
		i++;
	}
}
