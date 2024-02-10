#include "header.h"


int fix_input(char *line)
{
	epur_str(line);
	if (line[0] == '#')
		return (0);
	return (1);
}

void add_list(char **str, t_dblst *list)
{
	int i = 0;
	while (str[i] != NULL)
	{
		add_to_list(list, str[i]);
		i++;
	}
}

void tokenize_my_list(t_dblst *list)
{
	t_node *head = list->head;
	while (head)
	{
	}
	//print_list(list);
}

void find_path(char **str)
{
	int i = 0;
	char *env = getenv("PATH");
	char **path = ft_split(env, ':');
	int j = 0;
	while (path[j])
	{
		char *join1 = ft_strjoin(path[j], "/");
		char *join2 = ft_strjoin(join1, str[0]);
		free(join1);

		int fd = access(join2, F_OK);
		if (fd != -1)
					printf("%s\nFOUND IT!\n", join2);
		free(join2);
		j++;
	}
	while (str[i])
	{
		if (strchr(str[i], '|'))
		{
			int j = 0;
			while (path[j])
			{
				char *join1 = ft_strjoin(path[j], "/");
				char *join2 = ft_strjoin(join1, str[i + 1]);
				free(join1);

				int fd = access(join2, F_OK);
				if (fd != -1)
					printf("%s\nFOUND IT!\n", join2);
				free(join2);
				j++;
			}
			i++;
		}
		else
			i++;
	}
	//printf("%s\n", str[i]);
}

char *fix_line(char *str)
{ 
	int len = str_len(str);
	char *result = malloc(sizeof(char) * (len + 1));
	int j = 0; 

	int i = 0;
	while (i < len) 
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

int lexer(char *line, t_dblst *list)
{
	(void)list;
	if (!(fix_input(line)))
		return (0);
	char *fixed_line = fix_line(line);
	char **str = ft_split(fixed_line, ' ');
	int i = 0;
	while (str[i])
		printf("%s\n",str[i++]);
	//find_path(str);
	add_list(str, list);
	//tokenize_my_list(list);
	ft_free(str);
	return (1);
}




