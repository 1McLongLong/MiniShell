#include "header.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;

	//t_dblst list;
	while (1)
	{
		t_dblst list;
		list.head = NULL;
		list.tail = NULL;
		char *line = NULL;
		line = readline("~$ ");
		//char *env = getenv("PATH");
		//if (!(lexer(line, &list)))
			//line = readline("~$ ");
		lexer(line, &list);
		/*if (strchr(line, ';'))
		{
			char **str = ft_split(line, ';');
			int i = 0;
			while (str[i])
				add_to_list(&list, str[i++]);
			print_list(&list);
			free_list(&list);
		}
		else if (!(strcmp(line, "PATH")))
		{
			char **arr = ft_split(env, ':');
			int i = 0;
			while (arr[i])
				printf("%s\n", arr[i++]);
		}
		else*/
		//SEND_LIST();
		free_list(&list);
	}
}

/*
int main(void)
{
	char *path;
	path = getenv("PATH");
	if (!path)
		exit(1);
	char **arr = ft_split(path, ':');
	int i = 0;
	while (arr[i] != NULL)
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
	return (0);
}
*/


