#include "signals.h"


/**
 * sigquit_handler - handles the sigquit response
 * @signum: the number of the signal (SIGQUIT)
 * @info: pointer to siginfo_t
 * @context: pointer to ucontext_t (unused)
 *
 * Return: no return
 */

void sigquit_handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	if (signum == SIGQUIT && info != NULL)
	{
		printf("SIGQUIT sent by %d\n", info->si_pid);
		fflush(stdout);
	}
}

/**
 * trace_signal_sender - gives up PID of process that sent SIGQUIT
 *
 * Return: 0, -1
 */

int trace_signal_sender(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sigquit_handler;

	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		return (-1);
	}
	return (0);
}
