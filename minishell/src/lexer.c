#include "header.h"


int fix_input(char *line)
{
	epur_str(line);
	if (line[0] == '#')
		return (0);
	return (1);
}

char *fix_line(char *str)
{ 
	int len = str_len(str);
	char *result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	int j = 0; 

	int i = 0;
	while (i < len && j < len) 
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<') 
		{
			if (i > 0 && str[i - 1] != ' ')
			{
				result[j++] = ' '; 
			}
			result[j++] = str[i];
			if (i < len - 1 && str[i + 1] != ' ') 
			{
				result[j++] = ' '; 
			}
		} 
		else 
		{
			result[j++] = str[i];	
		}
		i++;
	}
	result[j] = '\0'; 
	return (result); 
}

int check_builtin(char *str)
{
	if (!str)
		return (0);
	if (!(strcmp(str, "echo")) || !(strcmp(str, "cd")) || !(strcmp(str, "pwd")) || !(strcmp(str, "exit")))
		return (1);
	else if (!(strcmp(str, "export")) || !(strcmp(str, "unset")) || !(strcmp(str, "env")))
		return (1);
	return (0);
}

void tokenize_my_list(t_dblst *list)
{
	t_node *head = list->head;
	head->type = TOKEN_COMMAND;
	head = head->next;
	while (head)
	{
		if (!(strcmp(head->cmd, "|")))
		{
			head->type = TOKEN_PIPE;
			head->next->type = TOKEN_COMMAND;
			head = head->next;
		}
		else if (strstr(head->cmd, "-"))
		{
			head->type = TOKEN_ARG;
		}
		else
			head->type = TOKEN_STRING;
		head = head->next;
	}
	print_list(list);
}

void find_path(char **str, t_dblst *list)
{
	int i = 0;
	char *env = NULL;
	env = getenv("PATH");
	if (env == NULL)
			printf("PATH IS GONE!!!");
	char **path = ft_split(env, ':');
	int j = 0;
	int path_flag = 0;
	while (path[j])
	{
		if (check_builtin(str[i]))
			break;
		char *join1 = ft_strjoin(path[j], "/");
		char *join2 = ft_strjoin(join1, str[i]);
		free(join1);

		int fd = access(join2, F_OK);
		if (fd != -1)
		{
			add_to_list(list, join2);
			path_flag = 1;
			i++;
		}
		free(join2);
		j++;
	}
	if (!path_flag && str[i])
		add_to_list(list, str[i++]);
	
	path_flag = 0;
	while (str[i])
	{
		if (strchr(str[i], '|'))
		{
			add_to_list(list, str[i]);
			i++;
			int j = 0;
			while (path[j])
			{
				if (check_builtin(str[i]))
					break;
				char *join1 = ft_strjoin(path[j], "/");
				char *join2 = ft_strjoin(join1, str[i]);
				free(join1);

				int fd = access(join2, F_OK);
				if (fd != -1)
				{
					add_to_list(list, join2);
					path_flag = 1;
				}
					//printf("%s\nFOUND IT!\n", join2);
				free(join2);
				j++;
			}
			if (!path_flag && str[i])
				add_to_list(list, str[i]);
			i++;
		}
		else
		{
			add_to_list(list, str[i]);
			i++;
		}
	}
	//printf("%s\n", str[i]);
}
/*
char *remove_shit(char *str)
{
	int i = 0;
	int len = ft_strlen(str) - get_len(str);
	char *res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	int j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '\\' || str[i] == '/' || str[i] == '(' || str[i] == ')')
			i++;
		else 
		{
			res[j] = str[i];
			i++;
			j++;
		}
	}
	res[j] = '\0';
	return (res);
}*/


int lexer(char *line, t_dblst *list)
{
	//t_dblst list_for_parse;
	//list_for_parse.head = NULL;
	//list_for_parse.tail = NULL;
	(void)list;
	if (!(fix_input(line)))
		return (0);
	char *fixed_line = fix_line(line);
	//char *line2 = remove_shit(fixed_line);
	//char **str = ft_split(line2, ' ');
	char **str_p = ft_split(fixed_line, ' ');
	//int i = 0;
	//while (str[i])
		//printf("%s\n",str[i++]);
	//find_path(str, list);
	add_list(str_p, list);
	//print_list(list);
	tokenize_my_list(list);
	ft_free(str_p);
	return (1);
}




