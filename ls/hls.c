#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include "hls.h"

/**
 * error_handler- handles all of our errors
 * @call_name: always argv[0]
 * @path: the path of the file or directory
 * @errno: the error number
 *
 * Return: no return
 */
void error_handler(char *call_name, const char *path, int errnum)
{
	if(errnum == -1)
	{
		fprintf(stderr,
			"%s: cannot access %s: No such file or directory\n", call_name, path);
	}
	if(errnum == -2)
	{
		fprintf(stderr,
			"%s: cannot open directory  %s: Permission denied\n", call_name, path);
	}
}

/**
 * list_directory- lists all the entries in a directory
 * @path: the path to the directory to open
 * @call_name: always argv[0];
 * Return: 0 on success, -1 on fail
 */

int list_directory(const char *path, char *call_name)
{
	DIR *dir;
	struct dirent *entry;
	struct stat data;

	if (stat(path, &data) == -1)
	{
		error_handler(call_name, path, -1);
		return (-1);
	}
	if (data.st_mode & !S_IXUSR)
	{
		error_handler(call_name, path, -2);
		return (-1);
	}
	if (S_ISREG(data.st_mode))
	{
		printf("%s\n", path);
		return (0);
	}
	dir = opendir(path);
	if (dir == NULL)
	{
		error_handler(call_name, path, -1);
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
	struct stat path_data;

	if (argc < 2)
	{
		path = ".";
		list_directory(path, argv[0]);
	}
	else if (argc == 2)
	{
		path = argv[1];
		if (list_directory(path, argv[0]) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		int i = 1;

		while (i <= argc - 1)
		{
			path = argv[i];
			if (lstat(path, &path_data) == -1)
			{
				i++;
				continue;
			}
			printf("%s:\n", path);
			list_directory(argv[i], argv[0]);
			printf("\n");
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
