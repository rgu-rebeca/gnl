#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h> 
#include "get_next_line_bonus.h"

int main(void)
{
    int fd1 = open("test_gnl.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    int fd3 = open("test3.txt", O_RDONLY);
    
    char *line;
    int i = 1;

    if (fd1 < 0 || fd2 < 0 || fd3 < 0)
    {
        perror("Error al abrir uno o más archivos");
        return (1);
    }

    printf("📜 Leyendo archivos en paralelo (Bonus Test)...\n");
    while (1)
    {
        line = get_next_line(fd1);
        if (line)
        {
            printf("[Archivo 1] Line %d: \"%s\"\n", i, line);
            free(line);
        }

        line = get_next_line(fd2);
        if (line)
        {
            printf("[Archivo 2] Line %d: \"%s\"\n", i, line);
            free(line);
        }

        line = get_next_line(fd3);
        if (line)
        {
            printf("[Archivo 3] Line %d: \"%s\"\n", i, line);
            free(line);
        }

        if (!line)
            break;

        i++;
    }
    close(fd1);
    close(fd2);
    close(fd3);

    printf("Prueba finalizada.\n");
    return (0);
}
