#define TEST_MODE 1

#if TEST_MODE == 1

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Error opening the file");
			return 1;
		}
	}
	else
	{
		printf("Error: incorrect number of arguments.\n");
		return (1);
	}

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}

	if (fd != 0)
		close(fd);

	return (0);
}

#elif TEST_MODE == 2

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return 1;
    }

    char *line;
    int i = 1;

    while ((line = get_next_line(fd)))
    {
        printf("Line %d: \"%s\"\n", i, line);
        free(line);
        i++;
    }

    printf("finished reading.\n");
    close(fd);

    return (0);
}
#endif
