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
	int inquotes = 0;

	int i = 0;
	while (i < len && j < len) 
	{
		if (str[i] == '"')
		{
			inquotes = !inquotes;
			result[j++] = str[i];
		}
		else if (!inquotes && (str[i] == '|' || str[i] == '>' || str[i] == '<')) 
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


/*
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
		else if (!(strcmp(head->cmd, "<")))
		{
			head->type = TOKEN_INFILE;
		}
		else if (!(strcmp(head->cmd, ">")))
		{
			head->type = TOKEN_OUTFILE;
		}
		else if (!(strcmp(head->cmd, ">>")))
		{
			head->type = TOKEN_DGREAT;
		}	
		else if (!(strcmp(head->cmd, "<<")))
		{
			head->type = TOKEN_DLESS;
		}
		else if (!(strcmp(head->cmd, "&")))
		{
			head->type = TOKEN_AMPERSAND;
		}
		else
			head->type = TOKEN_STRING;
		head = head->next;
	}
	print_list(list);
}
*/
"hello 'world "
int check_quotes(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == '\'')
		{

		}
	}
}

int lexer(char *line, t_dblst *list)
{
	(void)list;
	if (!(fix_input(line)))
		return (0);
	char *fixed_line = fix_line(line);
	if (check_quotes(fixed_line))
		return (0);
	printf("%s\n", fixed_line);
	char **str = ft_split(fixed_line, '|');
	//int i = 0;
	//while (str[i])
	//	printf("%s\n",str[i++]);
	//add_list(str, list);
	//print_list(list);
	//tokenize_my_list(list);
	ft_free(str);
	return (1);
}




