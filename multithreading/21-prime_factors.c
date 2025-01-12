#include "multithreading.h"

/**
 * prime_factors - finds all prime factors of string s
 * @s: the string (number)
 *
 * Return: list_t
 */

list_t *prime_factors(char const *s)
{
	list_t *list;
	char *endptr;
	unsigned long *factor;
	unsigned long i, number = strtoul(s, &endptr, 0);

	list = malloc(sizeof(list_t));
	if (!list)
		return (NULL);

	list_init(list);
	while (number % 2 == 0)
	{
		factor = create_factor(2);
		list_add(list, factor);
		number = number / 2;
	}

	for (i = 3; i * i <= number; i = i + 2)
	{
		while (number % i == 0)
		{
			factor = create_factor(i);
			list_add(list, factor);
			number = number / i;
		}
	}
	if (number > 2)
	{
		factor = create_factor(number);
		list_add(list, factor);
	}
	return (list);
}

/**
 * create_factor - creates a lu pointer with value
 * @value: the value
 *
 * Return: the pointer
 */

unsigned long *create_factor(unsigned long value)
{
	unsigned long *factor = malloc(sizeof(unsigned long));

	if (!factor)
		return (NULL);
	*factor = value;
	return (factor);
}
