#include "header.h"


char *find_dollar(char *str)
{
	int i = 0;
	int j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i;
			while (str[i]) // check that it's in the range of chars
		}
		
	}
}

void expand(x_node *p_list)
{
	x_node *temp = p_list;
	while (temp)
	{
		char *str = find_dollar(temp->str);
	}
}
