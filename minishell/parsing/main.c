/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:38:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/04 19:10:44 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int signal_catched;

void	handle_c(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	printf("\n~$ ");
}

void handle_signals()
{
	signal_catched = 0;
	signal(SIGINT, handle_c);
	// signal(SIGQUIT, SIG_IGN);
	// signal(EOF, handle_eof);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_dblst	list;

	handle_signals();
	while (1)
	{
		list.head = NULL;
		list.tail = NULL;
		char *line = NULL;
		line = readline("~$ ");
		if (line)
		{
			add_history(line);
			lexer(line, &list);
			print_list(&list);
		}
		free_list(&list);
		free(line);
	}
}

