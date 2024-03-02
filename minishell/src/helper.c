/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:47:03 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 16:58:30 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_free(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
	{
		free(lst[i]);
		i++;
	}
	free(lst);
}

void	remove_extra_spaces(char *str)
{
	char	*src;
	char	*dst;
	int		inside_quotes;

	src = str;
	dst = str;
	inside_quotes = 0;
	while (*src)
	{
		if (*src == '"')
		{
			inside_quotes = !inside_quotes;
			*dst++ = *src++;
		}
		else if (inside_quotes
			|| (*src != ' ' || (*(src + 1) != ' ' && *(src + 1) != '\0')))
			*dst++ = *src++;
		else
			src++;
	}
	*dst = '\0';
}

void	epur_str(char *str)
{
	char	*end;

	remove_extra_spaces(str);
	while (*str == ' ')
		str++;
	end = str;
	while (*end != '\0')
		end++;
	end--;
	while (end > str && *end == ' ')
	{
		*end = '\0';
		end--;
	}
}
