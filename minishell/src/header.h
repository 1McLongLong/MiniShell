#ifndef HEADER_H
# define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum    e_token_type
{
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_STRING,
	TOKEN_PIPE
}             t_token_type;

typedef struct node
{
	char *data;
  t_token_type  type;
	struct node	*prev;
	struct node	*next;
}				t_node;


typedef struct d_node
{
	t_node	*head;
	t_node	*tail;
} t_dblst;


int		ft_printf(const char *format, ...);
char	*get_next_line(int fd);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free(char **lst);

t_node	*create_node(char *data);
void	add_to_list(t_dblst *list, char *data);
void print_list(t_dblst *list);
void	free_list(t_dblst *list);

int lexer(char *line, t_dblst *list);
void epur_str(char *str); 
int str_len(const char *str);







#endif
