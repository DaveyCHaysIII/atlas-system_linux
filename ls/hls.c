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
	}
	else
	{
		path = argv[1];
	}
	if (list_directory(path) < 0)
	{
		perror("Error: ");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
