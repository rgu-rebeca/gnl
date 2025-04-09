#include "get_next_line.h"

static void	*read_and_store_aux(int fd, char **stored,
		ssize_t byte_read, char **buffer)
{
	char	*temp;

	while (!ft_strchr((*stored), '\n'))
	{
		byte_read = read (fd, (*buffer), BUFFER_SIZE);
		if (byte_read < 0)
			return (free(*buffer), free(*stored), NULL);
		if (byte_read == 0)
			break ;
		(*buffer)[byte_read] = '\0';
		temp = (*stored);
		*stored = ft_strjoin(*stored, *buffer);
		if (!(*stored))
		{
			free (*buffer);
			free (temp);
			return (NULL);
		}
		free(temp);
	}
	free(*buffer);
	if (byte_read == 0 && (!(*stored)[0]))
		return (free(*stored), NULL);
	return (*stored);
}

char	*read_and_store(int fd, char *stored)
{
	char	*buffer;
	ssize_t	byte_read;

	byte_read = 0;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!stored)
	{
		stored = ft_strdup("");
		if (!stored)
		{
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
	}
	stored = read_and_store_aux(fd, &stored, byte_read, &buffer);
	if (!stored)
		return (NULL);
	return (stored);
}

static char	*extract_line(char *stored)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stored || !stored[0])
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	line = (char *)malloc(i + (stored[i] == '\n') + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, stored, i + (stored[i] == '\n'));
	line[i + (stored[i] == '\n')] = '\0';
	return (line);
}

char	*update_stored(char *stored)
{
	size_t	i;
	char	*new_stored;

	i = 0;
	if (!stored)
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i] || !stored[i + 1])
	{
		free(stored);
		return (NULL);
	}
	new_stored = ft_strdup(stored + i + 1);
	if (!new_stored)
	{
		free (stored);
		return (NULL);
	}
	free(stored);
	return (new_stored);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	stored = read_and_store(fd, stored);
	if (!stored)
		return (NULL);
	line = extract_line(stored);
	if (!line)
	{
		free(stored);
		stored = NULL;
		return (NULL);
	}
	stored = update_stored(stored);
	return (line);
}
