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
