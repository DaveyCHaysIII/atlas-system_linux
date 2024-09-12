#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
#include "hls.h"

/**
 * list_directory- lists all the entries in a directory
 * @path: the path to the directory to open
 * @call_name: always argv[0]
 * @flags: pointer to flags array
 *
 * Return: 0 on success, -1 on fail
 */

int list_directory(const char *path, char *call_name, int *flags)
{
	DIR *dir;
	struct dirent *entry;
	struct stat data;

	if (S_ISREG(data.st_mode))
	{
		printf("%s\n", path);
		return (0);
	}
	else if (path_validator(path, call_name, &data))
	{
		dir = opendir(path);
		if (dir == NULL)
		{
			error_handler(call_name, path, -1);
			return (-1);
		}
		while ((entry = readdir(dir)) != NULL)
		{
			entry_path = path_maker(path, entry->d_name);
			lstat(entry_path, &data);
			print_handler(&entry, &data, &flags);
		}
		printf("\n");
		closedir(dir);
		return (0);
	}
	return (-1);
}

/**
 * entry_path- creates a direct path to a file
 * @path: the path to the parent directory
 * @name: the name of the file
 *
 * Return: the new path
 */
char *entry_path(const char *path, char* name)
{

}

/**
 * print_handler- handles the prints
 * @entry: the thing to print
 * @data: pointer to struct stat data
 * @entry: pointer to dirent entry
 * @flags: all the flags
 *
 * Return: no return
 */
void print_handler(struct dirent *entry, struct stat *data, int *flags)
{
	if (!flags[0])
	{
		printf("%s ", entry->d_name);
	}
	else
	{
		if (flags[1] && *entry->d_name == ".")
			return;
		if (flags[2] && (entry->d_name == "." || entry->d_name == ".."))
			return;
		if (flags[3])
		{
			printf("%s\n", entry->d_name);
		}
		/* flags 4, long format code here) */
	}
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
	int flags[] = {0, 0, 0, 0, 0}; /*flags, a, A, 1, l*/

	flag_init(flags, argc, argv);
	if (argc <= 2)
	{
		if (flags[0] || argc < 2)
		{
			path = ".";
			list_directory(path, argv[0], flags);
		}
		path = argv[1];
		if (list_directory(path, argv[0], flags) == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		int i = 1;

		while (i <= argc - 1)
		{
			path = argv[i];
			if (path_validator(path, argv(0), &path_data) == -1)
			{
				i++;
				continue;
			}
			printf("%s:\n", path);
			list_directory(argv[i], argv[0], flags);
			printf("\n");
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
