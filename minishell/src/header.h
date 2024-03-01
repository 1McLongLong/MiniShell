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

typedef struct indexes
{
	int i;
	int j;
	int len;
} t_index;

typedef struct s_node
{
	t_token_type type;
	char *str;
	int fd_in;
	int fd_out;
	struct s_node *prev;
	struct s_node *next;
} x_node;

typedef struct q_node
{
	x_node	*head;
	x_node	*tail;
} p_dblst;

typedef struct node
{
	char *cmd;
	char **arg; // echo hello world
	int fd_in;
	int fd_out;
	struct node	*prev;
	struct node	*next;
}				t_node;


typedef struct d_node
{
	t_node	*head;
	t_node	*tail;
} t_dblst;


int	ft_isalnum(int c);
int		ft_printf(const char *format, ...);
char	*get_next_line(int fd);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
//char	*ft_strjoin(char const *s1, char const *s2);
void	ft_free(char **lst);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_isalpha(int c);

t_node	*create_node(char *data);
char    **token_split(char const *s, char c);
void	add_to_list(t_dblst *list, char *data);
void print_list(t_dblst *list);
void add_list(char **str, t_dblst *list);
void	free_list(t_dblst *list);
void	free_slist(p_dblst *list);
void print(p_dblst *list);
void remove_quotes(p_dblst *p_list);
void redirections(p_dblst *list);
void expand_redir(char **str);

void expand(p_dblst *p_list);
p_dblst tokenize_list(char *str);
void lexer(char *line, t_dblst *list);
void epur_str(char *str); 
int str_len(char *str);
int get_len(char *str);
void fix_it_again(char *str);
char* fix_quotes(char *input);


char *exec_line(p_dblst *list);
void fix_e_line(char *f_line, char *e_line);
void remove_line_quotes(char *str);




#endif
