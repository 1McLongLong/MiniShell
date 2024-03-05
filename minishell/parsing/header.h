/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <touahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:46:56 by touahman          #+#    #+#             */
/*   Updated: 2024/03/05 21:40:57 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	COMMAND,
	ARG,
	STRING,
	PIPE,
	REDIN,
	REDOUT,
	APPEND,
	HERDOC,
	DELIMITER,
	INFILE,
	OUTFILE,
}	t_token_type;

typedef struct indexes
{
	int		i;
	int		j;
	int		len;
	int		end;
	int		fd;
	int		size;
	int		inquotes;
	int		inside_d_quotes;
	int		inside_s_quotes;
	char	*result;
	char	*expand;
	char	*temp;
	char	*temp2;
	char	*l_temp;
	char	*delimiter;
	char	*temp_file;
	char	*buffer;
}	t_index;

typedef struct state
{
	int	inside_d_quotes;
	int	inside_s_quotes;
	int	i;
	int	j;
}	t_state;

typedef struct s_node
{
	t_token_type	type;
	char			*str;
	int				fd_in;
	int				fd_out;
	struct s_node	*prev;
	struct s_node	*next;
}	t_pnode;

typedef struct q_node
{
	t_pnode	*head;
	t_pnode	*tail;
}	t_plist;

typedef struct node
{
	char		*cmd;
	char		**arg;
	int			fd_in;
	int			fd_out;
	struct node	*prev;
	struct node	*next;
}				t_node;

typedef struct d_node
{
	t_node	*head;
	t_node	*tail;
}	t_dblst;

int		ft_isalnum(int c);
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
char	*ft_strdup(const char *s1);
int		ft_isalpha(int c);
void	*ft_memset(void *b, int c, size_t len);

t_node	*create_node(char *data);
void	add_to_list(t_dblst *list, char *data);
void	add_list(char **str, t_dblst *list);
void	print_list(t_dblst *list);
void	free_list(t_dblst *list);
t_pnode	*create_snode(char *data);
void	add_to_slist(t_plist *list, char *data);
void	add_slist(char *str, t_plist *list);
char	**token_split(char const *s, char c);
void	free_slist(t_plist *list);
void	print(t_plist *list);
void	remove_quotes(t_plist *p_list);
void	redirections(t_plist *list);
void	expand_redir(char **str);
int		fix_input(char *line);
int		check_quotes(char *input);
int		check_syntax(t_plist *list);
void	quotes(t_pnode *p_list, char *env);

void	add_spaces_back(t_dblst *list);
void	remove_spaces(char *str);

void	heredoc(t_pnode *list);
void	expand(t_plist *p_list);
void	lexer(char *line, t_dblst *list);
void	epur_str(char *str);
int		str_len(char *str);
int		get_len(char *str);
int		count_len(char *input);
void	fix_it_again(char *str);
char	*fix_quotes(char *input);
t_plist	tokenize_list(char *str);

char	*exec_line(t_plist *list);
void	fix_e_line(char *f_line, char *e_line);
void	remove_line_quotes(char *str);
// TOKENIZER
void	mark_arguments(t_pnode *head);
void	mark_heredoc(t_pnode *head);
void	mark_redirection_output(t_pnode *head);
void	mark_redirection_input(t_pnode *head);
void	mark_pipes(t_pnode *head);

#endif
