#include "header.h"

/*
void herdoc(x_node *list)
{
  x_node *temp = list;
  // Assuming that temp->next->str contains the delimiter for heredoc
  const char *delimiter = temp->next->str;
  // Create a temporary file
  char temp_filename[] = "/tmp/heredoc_tempfile";
  int fd = open(temp_filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
  if (fd == -1) {
    perror("open");
    exit(EXIT_FAILURE);
  }
  // Read input until the delimiter is encountered
  char buffer[4096];
  while (1)
  {
    printf("heredoc> ");  // You might want to customize this prompt
    fgets(buffer, sizeof(buffer), stdin);

    if (strcmp(buffer, delimiter) == 0) {
      break;  // Stop reading when the delimiter is encountered
    }

    write(fd, buffer, strlen(buffer));
  }
  // Set the file descriptor for the next node in the list
  temp->next->fd_out = fd;
  // Close the temporary file
  close(fd);
  // Unlink (delete) the temporary file
  if (unlink(temp_filename) == -1) {
    perror("unlink");
    exit(EXIT_FAILURE);
  }
}
////////////
while (true)
{
  input_line = readline("> ");
  if (input_line == NULL)
    return (here_str);
  if (ft_strcmp(input_line, delimiter) == 0)
  {
    free(input_line);
    break ;
  }
  if (input_line != NULL && here_str != NULL)
  {
    here_str = delimcat(here_str, input_line, "\n");
    free(input_line);
  }
}
*/

void herdoc(x_node *list)
{
  x_node *temp = list;
}


void check_opened_fd(x_node *list, x_node *last_fnode)
{
  x_node *temp = list;

  while (temp != last_fnode)
  {
    if (temp->fd_out != 1)
    {
      close(temp->fd_out);
      temp->fd_out = -1;
    }
    else if (temp->fd_in != 0)
    {
      close(temp->fd_in);
      temp->fd_in = -1;
    }
    temp = temp->next;
  }
}


void redirections(x_node *list)
{
  x_node *temp;
  temp = list;

  while (temp)
  {
    if (strcmp(temp->str, ">") == 0)
    {
      check_opened_fd(list, temp);
      int fd = open(temp->next->str, O_CREAT | O_WRONLY | O_TRUNC);
      if (fd == -1)
        perror("ERROR");
      temp->next->fd_out = fd;
    }
    else if (strcmp(temp->str, "<") == 0)
    {
      check_opened_fd(list, temp);
      int fd = open(temp->next->str, O_RDONLY);
      if (fd == -1)
        perror("ERROR");
      temp->next->fd_out = fd;
    }
    else if (strcmp(temp->str, ">>") == 0)
    {
      check_opened_fd(list, temp);
      int fd = open(temp->next->str, O_CREAT | O_APPEND | O_WRONLY);
      if (fd == -1)
        perror("ERROR");
      temp->next->fd_out = fd;
    }
    else if (strcmp(temp->str, "<<") == 0)
    {
      check_opened_fd(list, temp);
      herdoc(temp);
    }
    temp = temp->next;
  }
}
