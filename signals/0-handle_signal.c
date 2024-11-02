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
 * handle_signal - handles a signal interrupt SIGINT
 *
 * Return: no return
 */

int handle_signal(void)
{
	if (signal(SIGINT, do_instead) == SIG_ERR)
		return (-1);
	else
		return (0);
}
