#include "signals.h"

/**
 * current_handler_sigaction - gives the address of the current signal handler
 *
 * Return: address of signal handler
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa, old_sa;

	if (sigaction(SIGINT, NULL, &old_sa) == -1)
	{
		return (NULL);
	}

	sa = old_sa;
	sa.sa_handler = SIG_IGN;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		return (NULL);
	}

	return (old_sa.sa_handler);
}
