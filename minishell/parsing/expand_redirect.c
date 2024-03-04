/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:13:54 by touahman          #+#    #+#             */
/*   Updated: 2024/03/04 15:05:00 by touahman         ###   ########.fr       */
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
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			break ;
		}
		i++;
	}
	if (j == -1)
		return (NULL);
	substring = malloc(sizeof(char) * (i - j + 1));
	if (!substring)
		return (NULL);
	ft_strlcpy(substring, &str[j + 1], i - j);
	return (substring);
}

// static void	redi_quotes(char **str, char *env)
// {
// 	t_index	index;
//
// 	index.i = 0;
// 	index.j = 0;
// 	index.expand = getenv(env);
// 	index.temp = NULL;
// 	if ((*str)[0] != '$')
// 	{
// 		while ((*str)[index.i] != '$')
// 			index.i++;
// 		index.temp = ft_substr(*str, 0, index.i);
// 	}
// 	while ((*str)[index.j])
// 		index.j++;
// 	index.end = index.j;
// 	while (!(ft_isalpha((*str)[index.j])) && (*str)[index.j] != '_')
// 		index.j--;
// 	index.j++;
// 	index.temp2 = ft_substr(*str, index.j, index.end - index.j);
// 	*str = ft_strjoin(index.temp, index.expand);
// 	index.l_temp = *str;
// 	*str = ft_strjoin(index.l_temp, index.temp2);
// }

static void	redi_quotes(char **str, char *env)
{
	t_index	index;
	char		*new_str;
	char		*substring_before;
	char		*substring_after;

	memset(&index, 0, sizeof(index));
	index.expand = getenv(env);
	while ((*str)[index.i] != '$' && (*str)[index.i])
		index.i++;
	substring_before = ft_substr(*str, 0, index.i);
	index.j = index.i + ft_strlen(env) + 1;
	while ((*str)[index.j] && (ft_isalnum((*str)[index.j]) || (*str)[index.j] == '_'))
		index.j++;
	substring_after = strdup(&(*str)[index.j]);
	index.temp = ft_strjoin(substring_before, index.expand);
	new_str = ft_strjoin(index.temp, substring_after);
	free(*str);
	free(substring_before);
	free(substring_after);
	free(index.temp);
	*str = new_str;
}

void	expand_redir(char **str)
{
	char	*env;

	env = find_dollar(*str);
	if (env)
	{
		redi_quotes(str, env);
		free(env);
	}
	return ;
}
