#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include "hls.h"

/**
 * list_directory- lists all the entries in a directory
 * @path: the path to the directory to open
 *
 * Return: 0 on success, -1 on fail
 */

int list_directory(const char *path)
{
	DIR *dir;
	struct dirent *entry;
	struct stat data;

	if (stat(path, &data) == -1)
	{
		perror("./hls_01: cannot access %s:", path);
		exit(EXIT_FAILURE);
	}
	if (S_ISREG(data.st_mode))
	{
		printf("%s\n", path);
		return (0);
	}
	dir = opendir(path);
	if (dir == NULL)
	{
		return (-1);
	}
	while ((entry = readdir(dir)) != NULL)
	{
		if (*entry->d_name != '.')
		{
			printf("%s ", entry->d_name);
		}
	}
	printf("\n");
	closedir(dir);
	return (0);
}

/**
 * main- entry point for ls
 * @argc: number of arguments passed
 * @argv: array of args
 *
 * Return: 0 on success, -1 on fail
 */

int main(int argc, char **argv)
{
	char *path;

	if (argc < 2)
	{
		path = ".";
		list_directory(path);
	}
	else if (argc == 2)
	{
		path = argv[1];
		list_directory(path);
	}
	else
	{
		int i = argc - 1;

		while (i > 0)
		{
			path = argv[i];
			printf("%s:\n ", path);
			list_directory(argv[i]);
			printf("\n");
			i--;
		}
	}
	return (EXIT_SUCCESS);
}
