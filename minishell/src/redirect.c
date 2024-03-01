#include "header.h"

int	delim_quotes(char *delim)
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

void	herdoc(x_node *list)
{
	x_node	*temp;
	char	*delimiter;
	char	*temp_file;
	char	*buffer;
	int		fd;

	temp_file = "/tmp/heredoc_tempfile";
	temp = list;
	delimiter = temp->next->str;
	fd = open(temp_file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("open");
	}
	while (1)
	{
		buffer = readline("> ");
		if (strcmp(buffer, delimiter) == 0)
		{
			free(buffer);
			break ;
		}
		if (delim_quotes(delimiter))
			expand_redir(&buffer);
		write(fd, buffer, strlen(buffer));
		write(fd, "\n", 1);
		free(buffer);
	}
	temp->next->fd_in = fd;
	 // close(fd);
//   fd = open(temp_filename, O_RDONLY);
//   if (fd == -1) {
//     perror("open");
//     exit(EXIT_FAILURE);
//   }

//   char ch;
//   while (read(fd, &ch, 1) == 1) {
//     putchar(ch);
//   }
  // close(fd);
  unlink(temp_file);
}


void	check_opened_fd(p_dblst *list, x_node *last_fnode, int flag)
{
	x_node	*temp;

	temp = list->head;
	while (temp != last_fnode)
		temp = temp->next;
	while (temp)
	{
		if (flag == 1 && temp->fd_out != 1)
		{
			close(temp->fd_out);
			temp->fd_out = -1;
		}
		else if (flag == 0 && temp->fd_in != 0)
		{
			close(temp->fd_in);
			temp->fd_in = -1;
		}
		if (temp->prev && strcmp(temp->prev->str, "|") == 0)
			break ;
		temp = temp->prev;
	}
}


void	redirections(p_dblst *list)
{
	x_node	*temp;
	int		fd;

	temp = list->head;
	while (temp)
	{
		if (strcmp(temp->str, ">") == 0 && temp->next)
		{
			check_opened_fd(list, temp, 1);
			fd = open(temp->next->str, O_CREAT | O_RDWR);
			if (fd == -1)
				perror("ERROR");
			temp->next->fd_out = fd;
		}
		else if (strcmp(temp->str, "<") == 0 && temp->next)
		{
			check_opened_fd(list, temp, 0);
			fd = open(temp->next->str, O_CREAT | O_RDONLY);
			if (fd == -1)
				perror("ERROR");
			temp->next->fd_in = fd;
		}
		else if (strcmp(temp->str, ">>") == 0 && temp->next)
		{
			check_opened_fd(list, temp, 1);
			fd = open(temp->next->str, O_CREAT | O_RDWR | O_TRUNC);
			if (fd == -1)
				perror("ERROR");
			temp->next->fd_out = fd;
		}
		else if (strcmp(temp->str, "<<") == 0 && temp->next)
		{
			check_opened_fd(list, temp, 0);
			herdoc(temp);
		}
		temp = temp->next;
	}
}
