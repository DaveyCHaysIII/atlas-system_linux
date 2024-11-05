#include "strings.h"

/**
 * main - the main file
 * @argc: num args
 * @argv: arg vec
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <pid>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (kill(atoi(argv[1]), SIGINT) == -1)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
