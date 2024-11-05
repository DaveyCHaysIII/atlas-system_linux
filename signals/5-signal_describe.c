#include "signals.h"

/**
 * main - entry to function
 * @argc: num args
 * @argv: arg vec
 *
 * Return: 0, -1
 */

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	printf("%s: %s\n", argv[1], strsignal(atoi(argv[1])));
	return (0);
}
