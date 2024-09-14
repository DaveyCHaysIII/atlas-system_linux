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
	char *entry_path;

	if (path_validator(path, call_name, &data) == 0)
	{
		if(S_ISREG(data.st_mode))
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
			entry_path = path_maker(path, entry->d_name);
			print_handler(entry, &data, flags);
			free(entry_path);
		}
		if (!(flags[3] || flags[4]))
		{
			printf("\n");
		}
		closedir(dir);
		return (0);
	}
	return (-1);
}

/**
 * path_maker- creates a direct path to a file
 * @path: the path to the parent directory
 * @name: the name of the file
 *
 * Return: the new path
 */
char *path_maker(const char *path, char* name)
{
	int len_path = strlen(path);
	int len_filename = strlen(name);
	char *path_new = malloc(len_path + len_filename + 2);
	if (path == NULL)
	{
		exit(EXIT_FAILURE);
	}
	sprintf(path_new, "%s/%s", path, name);
	return (path_new);
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
		if (*entry->d_name != '.')
		{
			printf("%s ", entry->d_name);
		}
	}
	else
	{
		int is_dot = strcmp(entry->d_name, ".");
		int is_dot_dot = strcmp(entry->d_name, "..");
		if (!flags[1] && *entry->d_name == '.')
		{
			return;
		}
		else if (flags[2] && (is_dot == 0 || is_dot_dot == 0))
			return;
		else if (flags[3])
			printf("%s\n", entry->d_name);
		else if (flags[4])
			printf("Placeholder for list: %ld\n", data->st_size);
		else
			printf("%s ", entry->d_name);
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
	if (argc <= 2 || (argc == 3 && flags[0]))
	{
		if (flags[0] || argc < 2)
		{
			path = ".";
			list_directory(path, argv[0], flags);
			return (0);
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
			if (path_validator(path, argv[0], &path_data) == -1)
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
