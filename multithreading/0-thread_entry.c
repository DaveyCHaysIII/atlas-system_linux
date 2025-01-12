#include "multithreading.h"

/**
 * thread_entry - entry point for a thread
 * @arg: the argument to print
 *
 * Return: void pointer (NULL)
 */

void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
}
