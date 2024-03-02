#include "header.h"

static int	delim_quotes(char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == '\"' || delim[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

void	heredoc(x_node *list)
{
	x_node	*temp;
	t_index	index;

	index.temp_file = "/tmp/heredoc_tempfile";
	temp = list;
	index.delimiter = temp->next->str;
	index.fd = open(index.temp_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (index.fd == -1)
		perror("open");
	while (1)
	{
		index.buffer = readline("> ");
		if (strcmp(index.buffer, index.delimiter) == 0)
		{
			free(index.buffer);
			break ;
		}
		if (delim_quotes(index.delimiter))
			expand_redir(&index.buffer);
		write(index.fd, index.buffer, strlen(index.buffer));
		write(index.fd, "\n", 1);
		free(index.buffer);
	}
	temp->next->fd_in = index.fd;
	unlink(index.temp_file);
}