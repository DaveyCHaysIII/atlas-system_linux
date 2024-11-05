#include "signals.h"

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C)
 * @signum: The signal number
 */

void sigint_handler(int signum) {
	printf("Caught %d\n", signum);
	printf("Signal received\n");
	fflush(stdout);

	exit(EXIT_SUCCESS);
}

/**
 * main - entry for function
 *
 * Return: 0, -1
 */

int main(void)
{
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		exit(EXIT_FAILURE);
	}

	pause();

	return (EXIT_SUCCESS);
}
