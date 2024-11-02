#include "signals.h"

/**
 * current_handler_signal - gives the address of the current signal handler
 *
 * Return: address of signal handler
 */

void(*current_handler_signal(void))(int)
{
	void (*prev_handler)(int) = signal(SIGINT, SIG_IGN);

	if (prev_handler == SIG_ERR)
	{
		return (NULL);
	}
	signal(SIGINT, prev_handler);
	return (prev_handler);
}
