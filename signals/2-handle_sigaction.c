#include "signals.h"

/**
 * do_instead - signal handler
 * @signum: the signum in question
 *
 * Return: no return
 */

void do_instead(int signum)
{
	printf("Gotcha! [%d]\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - handles SIGINT
 *
 * Return: no return
 */

int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_handler = do_instead;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		return (-1);
	}
	return (0);
}
