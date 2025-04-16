/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:39:35 by rgu               #+#    #+#             */
/*   Updated: 2025/04/09 16:39:36 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (free(*stored), *stored = NULL, line);
	new_stored = ft_strdup((*stored) + i + 1);
	if (new_stored)
	{
		free(*stored);
		*stored = new_stored;
	}
	return (line);
}

void	*get_next_line_aux(ssize_t byte_read,
		char **buffer, t_fd_list **current_fd, int fd)
{
	char	*temp;

	while (byte_read > 0)
	{
		(*buffer)[byte_read] = '\0';
		temp = ft_strjoin((*current_fd)-> stored, *buffer);
		if (!temp)
		{
			free(*buffer);
			*buffer = NULL;
			if ((*current_fd)-> stored)
			{
				free ((*current_fd)-> stored);
				(*current_fd)-> stored = NULL;
			}
			return (NULL);
		}
		free((*current_fd)-> stored);
		(*current_fd)-> stored = temp;
		if (ft_strchr((*current_fd)-> stored, '\n'))
			break ;
		byte_read = read (fd, *buffer, BUFFER_SIZE);
	}
	free(*buffer);
	return (*current_fd);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	t_fd_list			*current_fd;
	char				*buffer;
	ssize_t				byte_read;

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
		return (free(buffer), buffer = NULL, remove_node(&fd_list, fd), NULL);
	current_fd = get_next_line_aux (byte_read, &buffer, &current_fd, fd);
	if (!current_fd -> stored || !current_fd -> stored[0])
		return (remove_node(&fd_list, fd), NULL);
	return (extract_line(&current_fd -> stored));
}
