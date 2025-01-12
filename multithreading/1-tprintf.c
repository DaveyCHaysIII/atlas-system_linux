#include "multithreading.h"

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

	va_start(ptr, format);

	printf("[%lu] ", id);
	ret = vprintf(format, ptr);

	va_end(ptr);

	return ((ret < 0) ? 1 : 0);
}
