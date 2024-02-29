#include "header.h"

void f()
{
	system("leaks minishell");
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	//t_dblst list;
	while (1)
	{
		// e_node *env_list = NULL;
		// atexit(f);
		t_dblst list;
		list.head = NULL;
		list.tail = NULL;
		char *line = NULL;
		line = readline("~$ ");
		//if (!(lexer(line, &list)))
			//line = readline("~$ ");
		// get_env(&env_list, env);
		lexer(line, &list);
		// free_envlist(env_list);
		free_list(&list);
		free(line);
		// break;
	}
}

