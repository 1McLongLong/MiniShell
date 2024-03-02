/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:38:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/02 14:39:36 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_dblst	list;

	while (1)
	{
		list.head = NULL;
		list.tail = NULL;
		char *line = NULL;
		line = readline("~$ ");
		//if (!(lexer(line, &list)))
			//line = readline("~$ ");
		// get_env(&env_list, env);
		lexer(line, &list);
		print_list(&list);
		free_list(&list);
		free(line);
	}
}

