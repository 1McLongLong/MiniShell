#include "header.h"


char *exec_line(p_dblst *list) 
{
  x_node *head;
  char *result;
  int length;
  int i;

  if (list->head == NULL) 
    return NULL;
  head = list->head;
  length = 0;
  while (head != NULL)
  {
    length += strlen(head->str) + 1;
    head = head->next;
  }

  result = (char *)malloc(length + 1);
  if (result == NULL) {
    perror("Memory allocation error");
    exit(EXIT_FAILURE);
  }
  head = list->head;
  i = 0;
  while (head != NULL) 
  {
    strcpy(result + i, head->str);
    i += strlen(head->str);
    result[i++] = ' ';
    head = head->next;
  }
  result[length - 1] = '\0';
  return (result);
}




