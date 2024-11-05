#include "signals.h"

/**
 * current_handler_sigaction - gives the address of the current signal handler
 *
 * Return: address of signal handler
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction old_sa;

	if (sigaction(SIGINT, NULL, &old_sa) == -1)
	{
		return (NULL);
	}

	return (old_sa.sa_handler);
}
