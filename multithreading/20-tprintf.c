#include "multithreading.h"

static pthread_mutex_t tprintf_mutex;

/**
 * tprintf_init - initializes the mutex
 *
 * Return: no return
 */
__attribute__((constructor))
static void tprintf_init(void)
{
	pthread_mutex_init(&tprintf_mutex, NULL);
}

/**
 * tprintf_destroy - destroys the mutex
 *
 * Return: no return
 */
__attribute__((destructor))
static void tprintf_destroy(void)
{
	pthread_mutex_destroy(&tprintf_mutex);
}

/**
 * tprintf - prints a formatted string
 * @format: the string to print
 *
 * Return: 0 or 1
 */

int tprintf(char const *format, ...)
{
	pthread_t id;
	va_list ptr;
	int ret;

	id = pthread_self();
	pthread_mutex_lock(&tprintf_mutex);

	va_start(ptr, format);

	printf("[%lu] ", id);
	ret = vprintf(format, ptr);

	va_end(ptr);
	pthread_mutex_unlock(&tprintf_mutex);

	return ((ret < 0) ? 1 : 0);
}
