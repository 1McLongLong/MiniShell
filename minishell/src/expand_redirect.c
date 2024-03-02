/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:13:54 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 15:25:57 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*find_dollar(char *str)
{
	char	*substring;
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i;
			i++;
			while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
					|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
				i++;
			break ;
		}
		i++;
	}
	if (j == -1)
		return (NULL);
	substring = malloc(sizeof(char) * (i - j));
	ft_strlcpy(substring, &str[j + 1], i - j);
	return (substring);
}

static void	red_quotes(char **str, char *env)
{
	t_index	index;

	index.i = 0;
	index.j = 0;
	index.expand = getenv(env);
	index.temp = NULL;
	if ((*str)[0] != '$')
	{
		while ((*str)[index.i] != '$')
			index.i++;
		index.temp = ft_substr(*str, 0, index.i);
	}
	while ((*str)[index.j])
		index.j++;
	index.end = index.j;
	while (!(ft_isalpha((*str)[index.j])) && (*str)[index.j] != '_')
		index.j--;
	index.j++;
	index.temp2 = ft_substr(*str, index.j, index.end - index.j);
	*str = ft_strjoin(index.temp, index.expand);
	index.l_temp = *str;
	*str = ft_strjoin(index.l_temp, index.temp2);
}

void	expand_redir(char **str)
{
	char	*env;

	env = find_dollar(*str);
	if (env != NULL)
	{
		red_quotes(str, env);
		free(env);
	}
	return ;
}
