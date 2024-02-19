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
	DOLLAR, // 0
	DOLLAR_IN, // 1
	DOLLAR_OUT, // 2
	COMMAND, // 3
	ARG, // 4
	STRING, // 5
	PIPE, // 6
	REDIN, // 7
	REDOUT, // 8
	APPEND, // 9
	HERDOC, // 10
	DELIMITER, // 11
	INFILE, // 12
	OUTFILE, // 13
}             t_token_type;

typedef struct s_node
{
	t_token_type type;
	char *str;
	struct s_node *next;
} x_node;

typedef struct node
{
	char *cmd;
	char **arg;
	int fd_in;
	int fd_out;
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
size_t	ft_strlen(const char *s);

t_node	*create_node(char *data);
void	add_to_list(t_dblst *list, char *data);
void print_list(t_dblst *list);
void add_list(char **str, t_dblst *list);
void	free_list(t_dblst *list);
void print(x_node *list);

x_node *tokenize_list(char *str);
void lexer(char *line, t_dblst *list);
void epur_str(char *str); 
int str_len(const char *str);
int get_len(char *str);
void fix_it_again(char *str);







#endif
