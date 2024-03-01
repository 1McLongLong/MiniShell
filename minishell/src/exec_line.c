#include "header.h"

char *exec_line(p_dblst *list) 
{
	x_node *head;
	char *result;
	t_index index;

	memset(&index, 0, sizeof(index));
	if (list->head == NULL) 
		return (NULL);
	head = list->head;
	while (head != NULL)
	{
		index.len += strlen(head->str) + 1;
		head = head->next;
	}
	result = (char *)malloc(index.len + 1);
	if (result == NULL)
		return (NULL);
	head = list->head;
	while (head != NULL) 
	{
		strcpy(result + index.i, head->str);
		index.i += strlen(head->str);
		result[index.i++] = ' ';
		head = head->next;
	}
	result[index.len - 1] = '\0';
	return (result);
}


// void fix_e_line(const char *f_line, char *e_line) 
// {
// 	const char *f_quote = f_line;
// 	char *e_quote = e_line;
//
// 	// Iterate over each pair of quotes in f_line and e_line
// 	while ((f_quote = strchr(f_quote, '\"')) && (e_quote = strchr(e_quote, '\"')))
// 	{
// 		// Check if there is no space before the quote in f_line
// 		if (*(f_quote - 1) != ' ') {
// 			// Check if there is a space before the quote in e_line
// 			if (*(e_quote - 1) == ' ') {
// 				// Remove the space before the quote in e_line
// 				memmove(e_quote - 1, e_quote, strlen(e_quote) + 1);
// 			}
// 		}
//
// 		// Check if there is no space after the quote in f_line
// 		if (*(f_quote + 1) != ' ' && *(f_quote + 1) != '\0') {
// 			// Check if there is a space after the quote in e_line
// 			if (*(e_quote + 1) == ' ') {
// 				// Remove the space after the quote in e_line
// 				memmove(e_quote + 1, e_quote + 2, strlen(e_quote + 1) + 1);
// 			}
// 		}
// 		// Move to the next quote in f_line and e_line
// 		f_quote++;
// 		e_quote++;
// 	}
// }

static void e_quotes(char *f_line, char *e_line, char quote_type)
{
	char *f_quote;
	char *e_quote;
	char quote_char;

	f_quote = f_line;
	e_quote = e_line;
	if (quote_type == '"')
		quote_char = '"';
	else 
		quote_char = '\'';
	while ((f_quote = strchr(f_quote, quote_char)) && (e_quote = strchr(e_quote, quote_char))) 
	{
		if (f_quote != f_line && *(f_quote - 1) != ' ') 
		{
			if (e_quote != e_line && *(e_quote - 1) == ' ')
				memmove(e_quote - 1, e_quote, strlen(e_quote) + 1);
		}
		if (*(f_quote + 1) != ' ' && *(f_quote + 1) != '\0')
		{
			if (*(e_quote + 1) == ' ' && *(e_quote + 1) != '\0')
				memmove(e_quote + 1, e_quote + 2, strlen(e_quote + 1) + 1);
		}
		f_quote++;
		e_quote++;
	}
}

void fix_e_line(char *f_line, char *e_line) 
{
	e_quotes(f_line, e_line, '"');
	e_quotes(f_line, e_line, '\'');
}
