#include "header.h"


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
			int fd = open(temp->next->str, O_CREAT | O_RDWR);
			if (fd == -1)
				perror("ERROR");
			temp->next->fd_out = fd;
		}
		else if (strcmp(temp->str, "<") == 0)
		{
			check_opened_fd(list, temp);
			int fd = open(temp->next->str, O_CREAT | O_RDONLY);
			if (fd == -1)
				perror("ERROR");
			temp->next->fd_out = fd;
		}
		else if (strcmp(temp->str, ">>") == 0)
		{
			check_opened_fd(list, temp);
			int fd = open(temp->next->str, O_CREAT | O_RDWR | O_TRUNC);
			if (fd == -1)
				perror("ERROR");
			temp->next->fd_out = fd;
		}
		/*else if (strcmp(temp->str, "<<") == 0)
		{
			check_opened_fd(list, temp);
			herdoc(temp);
		}*/
		temp = temp->next;
	}
}
