#include "get_next_line_bonus.h"

static t_fd_list	*find_or_create(int fd, t_fd_list **head)
{
	t_fd_list	*temp;

	temp = *head;
	while (temp)
	{
		if (temp -> fd == fd)
			return (temp);
		temp = temp -> next;
	}
	temp = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!temp)
		return (NULL);
	temp -> fd = fd;
	temp -> stored = NULL;
	temp -> next = *head;
	*head = temp;
	return (*head);
}

static void	remove_node(t_fd_list **head, int fd)
{
	t_fd_list	*prv;
	t_fd_list	*current;

	current = *head;
	prv = NULL;
	while (current)
	{
		if (current -> fd == fd)
		{
			if (prv)
				prv -> next = current -> next;
			else
				*head = current -> next;
			if (current -> stored)
			{
				free(current -> stored);
				current -> stored = NULL;
			}
			free(current);
			return ;
		}
		prv = current;
		current = current -> next;
	}
}

static char	*extract_line(char **stored)
{
	char	*line;
	size_t	i;
	char	*new_stored;

	i = 0;
	if (!(*stored) || !(*stored)[0])
		return (NULL);
	while ((*stored)[i] && (*stored)[i] != '\n')
		i++;
	line = (char *)malloc(i + ((*stored)[i] == '\n') + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *stored, i + ((*stored)[i] == '\n'));
	line[i + ((*stored)[i] == '\n')] = '\0';
	if (!(*stored)[i])
	{
		free(*stored);
		*stored = NULL;
	}
	else
	{
		new_stored = ft_strdup((*stored) + i + 1);
		if (new_stored)
		{
			free(*stored);
			*stored = new_stored;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	t_fd_list			*current_fd;
	char				*buffer;
	ssize_t				byte_read;
	char				*temp;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd = find_or_create(fd, &fd_list);
	if (!current_fd)
		return (NULL);
	buffer = (char *)malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byte_read = read (fd, buffer, BUFFER_SIZE);
	if (byte_read < 0 || (byte_read == 0
			&& (!current_fd -> stored || !current_fd -> stored[0])))
	{
		free(buffer);
		buffer = NULL;
		remove_node(&fd_list, fd);
		return (NULL);
	}
	while (byte_read > 0)
	{
		buffer[byte_read] = '\0';
		temp = ft_strjoin(current_fd -> stored, buffer);
		if (!temp)
		{
			free(buffer);
			buffer = NULL;
			if (current_fd -> stored)
			{
				free (current_fd -> stored);
				current_fd -> stored = NULL;
			}
			return (NULL);
		}
		free(current_fd -> stored);
		current_fd -> stored = temp;
		if (ft_strchr(current_fd -> stored, '\n'))
			break ;
		byte_read = read (fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (!current_fd -> stored || !current_fd -> stored[0])
	{
		remove_node(&fd_list, fd);
		return (NULL);
	}
	return (extract_line(&current_fd -> stored));
}

/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd1 = open("test_gnl.txt", O_RDONLY);
	//int fd2 = open("test2.txt", O_RDONLY);
	//int fd3 = open("test3.txt", O_RDONLY);
    char *line;
    int i = 1;

   while ((line = get_next_line(fd1)))
    {
        printf("Line %d: \"%s\"\n", i, line);
        free(line);
        i++;
    }
    printf("Final get_next_line() returned: %s\n", line);
	while ((line = get_next_line(fd2)))
    {
        printf("Line %d: \"%s\"\n", i, line);
        free(line);
        i++;
    }
    printf("Final get_next_line() returned: %s\n", line);
	while ((line = get_next_line(fd3)))
    {
        printf("Line %d: \"%s\"\n", i, line);
        free(line);
        i++;
    }
    printf("Final get_next_line() returned: %s\n", line);
    close(fd1);
	//close(fd2);
	//close(fd3);
}*/