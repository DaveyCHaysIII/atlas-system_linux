#include"hls.h"

/**
 * _strlen- gives the lenght of a string
 * @string: the string in question
 *
 * Return: lenght of string
 */
int _strlen(const char *string)
{
	int i = 0;

	while (string[i] != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * _strcmp - compares two strings.
 * @s1: the first string.
 * @s2: the second string.
 *
 * Return: an integer less than, equal to, or greater than zero if s1 is
 *         lexicographically less than, equal to, or greater than s2.
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * list_count- counts how many arguments are not flags
 * @argv: pointer to the argument vector to parse
 * @argc: number of entries to parse
 *
 * Return: number parsed
 */
int list_count(int argc, char **argv)
{
	int i = 1;
	int j = 0;

	while (i < argc)
	{
		if (*argv[i] != '-')
			j++;
		i++;
	}
	return (j);
}
