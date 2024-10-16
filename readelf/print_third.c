#include "readelf.h"

/**
 * print_flags - print the flags
 *
 * Return: no return
 */
void print_flags(void)
{
	printf("  Flags:                             0x0\n");
}

/**
 * print_headersize - print the size of the header
 * @e_ehsize: the size of the header
 *
 * Return: no return
 */
void print_headersize(uint16_t e_ehsize)
{
	printf("  Size of this header:               ");
	printf("%u (bytes)\n", (unsigned int)e_ehsize);
}
