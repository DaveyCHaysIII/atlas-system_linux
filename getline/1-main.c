#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "_getline.h"

/**
 * main - entry point.
 *
 * Return: always 0.
 */
int main(void)
{
	int fd1, fd2;
	char *line;

	fd1 = open("2-main.c", 0);
	fd2 = open("laps.h", 0);
	while ((line = _getline(fd1)))
	{
		printf("%s\n", line);
		free(line);
	}
	while ((line = _getline(fd2)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd1);
	close(fd2);
	return (0);
}
