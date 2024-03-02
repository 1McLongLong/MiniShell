/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:37:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 15:24:47 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	process_double_quotes(x_node *p_list, char *env, t_index *index)
{
	index->expand = getenv(env);
	while (p_list->str[index->i] != '$')
		index->i++;
	index->temp = ft_substr(p_list->str, 0, index->i);
	while (p_list->str[index->j])
		index->j++;
	index->end = index->j;
	while (index->j > 0 && !(ft_isalnum(p_list->str[index->j]))
		&& p_list->str[index->j] != '_')
		index->j--;
	index->j++;
	index->temp2 = ft_substr(p_list->str, index->j, index->end - index->j);
	p_list->str = ft_strjoin(index->temp, index->expand);
	index->l_temp = p_list->str;
	p_list->str = ft_strjoin(index->l_temp, index->temp2);
}

void	process_single_quotes(x_node *p_list, t_index *index)
{
	while (p_list->str[index->i])
		index->i++;
	index->temp = ft_substr(p_list->str, 0, index->i);
	free(p_list->str);
	p_list->str = strdup(index->temp);
	free(index->temp);
}

void	process_no_quotes(x_node *p_list, char *env, t_index *index)
{
	index->expand = getenv(env);
	index->temp = NULL;
	if (p_list->str[0] != '$')
	{
		while (p_list->str[index->i] != '$')
			index->i++;
		index->temp = ft_substr(p_list->str, 0, index->i);
	}
	while (p_list->str[index->j])
		index->j++;
	index->end = index->j;
	while (index->j >= 0 && !(ft_isalnum(p_list->str[index->j]))
		&& p_list->str[index->j] != '_')
		index->j--;
	index->j++;
	index->temp2 = ft_substr(p_list->str, index->j, index->end - index->j);
	p_list->str = ft_strjoin(index->temp, index->expand);
	index->l_temp = p_list->str;
	p_list->str = ft_strjoin(index->l_temp, index->temp2);
}

void	quotes(x_node *p_list, char *env)
{
	t_index	index;

	memset(&index, 0, sizeof(index));
	while (p_list->str[index.i])
	{
		if (p_list->str[0] == '"')
			process_double_quotes(p_list, env, &index);
		else if (p_list->str[0] == '\'')
			process_single_quotes(p_list, &index);
		else
			process_no_quotes(p_list, env, &index);
		break ;
	}
}
