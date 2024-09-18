#include "hls.h"

/**
 * error_handler- handles all of our errors
 * @call_name: always argv[0]
 * @path: the path of the file or directory
 * @errnum: the error number
 *
 * Return: no return
 */
void error_handler(char *call_name, const char *path, int errnum)
{
	if (errnum == -1)
	{
		fprintf(stderr,
			"%s: cannot access %s: No such file or directory\n", call_name, path);
	}
	if (errnum == -2)
	{
		fprintf(stderr,
			"%s: cannot open directory %s: Permission denied\n", call_name, path);
	}
}

/**
 * path_validator- validates a path
 * @path: the path to validate
 * @call_name: always argv[0]
 * @path_data: struct stat pointer
 *
 * Return: 0 on success, -1 for error, 1 for flags
 */
int path_validator(const char *path, char *call_name, struct stat *path_data)
{
	if (*path == '-')
	{
		return (-1);
	}
	else
	{
		if (lstat(path, path_data) == -1)
		{
			error_handler(call_name, path, -1);
			return (-1);
		}
		if (S_ISREG(path_data->st_mode))
		{
			return (0);
		}
		else if (!(path_data->st_mode & S_IXUSR))
		{
			error_handler(call_name, path, -2);
			return (-1);
		}
		return (0);
	}
}

/**
 * flag_init- initializes the flag array
 * @flags: pointer to array in question
 * @argc: number of arguments to parse through
 * @argv: array of strings to parse through
 *
 * Return: no return
 */
void flag_init(int *flags, int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
	{
		if ((argv[i][0]) == '-')
		{
			flags[0] = 1;
			int j = 1;

			while (argv[i][j] != '\0')
			{
				if (argv[i][j] == 'a')
				{
					flags[1] = 1;
				}
				else if (argv[i][j] == 'A')
				{
					flags[1] = 1;
					flags[2] = 1;
				}
				else if (argv[i][j] == '1')
				{
					flags[3] = 1;
				}
				else if (argv[i][j] == 'l')
				{
					flags[4] = 1;
				}
				else
				{
					fprintf(stderr,
						"%s: invalid option -- %s\n", argv[0], argv[i]);
					exit(EXIT_FAILURE);
				}
				j++;
			}
		}
	}
}

/**
 * multi_print- prints multiple directories
 * @argc: length of argv
 * @argv: argument vector
 * @path_data: pointer to struct stat
 * @flags: pointer to flags array
 *
 * Return: no return
 */
void multi_print(int argc, char **argv, struct stat *path_data, int *flags)
{
	char *path;
	int i;

	i = 1;
	while (i <= argc - 1)
	{
		path = argv[i];
		if (path_validator(path, argv[0], path_data) == -1)
		{
			i++;
			continue;
		}
		if (S_ISDIR(path_data->st_mode))
		{
			printf("%s:\n", path);
		}
		list_directory(argv[i], argv[0], flags);
		printf("\n");
		i++;
	}
}

/**
 * print_file_info- prints the -l version of a file
 * @entry: struct dirent for file
 * @file_stat: the struct stat that contains the file information
 *
 * Return: no return
 */
void print_file_info(struct dirent *entry, struct stat *file_stat)
{
	struct passwd *pwd;
	struct group *grp;
	char *mod_time;
	char formatted_time[13];

	printf((S_ISDIR(file_stat->st_mode)) ? "d" : "-");
	printf((file_stat->st_mode & S_IRUSR) ? "r" : "-");
	printf((file_stat->st_mode & S_IWUSR) ? "w" : "-");
	printf((file_stat->st_mode & S_IXUSR) ? "x" : "-");
	printf((file_stat->st_mode & S_IRGRP) ? "r" : "-");
	printf((file_stat->st_mode & S_IWGRP) ? "w" : "-");
	printf((file_stat->st_mode & S_IXGRP) ? "x" : "-");
	printf((file_stat->st_mode & S_IROTH) ? "r" : "-");
	printf((file_stat->st_mode & S_IWOTH) ? "w" : "-");
	printf((file_stat->st_mode & S_IXOTH) ? "x" : "-");
	printf(" ");

	printf("%lu ", file_stat->st_nlink);

	pwd = getpwuid(file_stat->st_uid);
	grp = getgrgid(file_stat->st_gid);
	if (pwd)
		printf("%s ", pwd->pw_name);
	else
		printf("%d ", file_stat->st_uid);

	if (grp)
		printf("%s ", grp->gr_name);
	else
		printf("%d ", file_stat->st_gid);

	printf("%ld ", file_stat->st_size);

	mod_time = ctime(&file_stat->st_mtime);
	sprintf(formatted_time, "%.3s %.2s %.4s",
		mod_time + 4, mod_time + 8, mod_time + 20);
	printf("%s ", formatted_time);

	printf("%s\n", entry->d_name);
}
