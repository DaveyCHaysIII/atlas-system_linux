#include <unistd.h>
#include <signal.h>

/**
 * pid_exist - checks if a pid exists
 * @pid: the pid in question
 *
 * Return: pid or 0
 */

int pid_exist(pid_t pid)
{
	return (kill(pid, 0) == 0);
}

