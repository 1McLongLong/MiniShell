/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:38:38 by touahman          #+#    #+#             */
/*   Updated: 2024/03/05 12:46:13 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	handle_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_eof(int sig)
{
	(void)sig;
}

void	handle_signals(void)
{
	rl_catch_signals = 0;
	// signal(SIGINT, handle_c);
	signal(SIGQUIT, SIG_IGN);
	signal(EOF, handle_eof);
}

int	main(int argc, char **argv, char **env)
{
	t_dblst	list;
	char	*line;

	(void)argc;
	(void)argv;
	(void)env;
	handle_signals();
	while (1)
	{
		list.head = NULL;
		list.tail = NULL;
		line = NULL;
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
