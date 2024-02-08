#include "header.h"


void epur_str(char *str) 
{
	int i = 0;
	int j = 0;

	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
		i++;
	while (str[i] && (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'))
		str[j++] = str[i++];

	while (str[i]) 
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (str[i])
			str[j++] = ' ';
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			str[j++] = str[i++];
	}
	str[j] = '\0';
}
