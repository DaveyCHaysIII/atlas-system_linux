#include "readelf.h"

/**
 * print_progheadersize - prints the size of the prog headers
 * @e_phentsize: the size of the prog headers
 *
 * Return: no return
 */
void print_progheadersize(uint16_t e_phentsize)
{
	printf("  Size of program headers:           ");
	printf("%u (bytes)\n", (unsigned short)e_phentsize);
}

/**
 * print_numprograms - prints the number of programs
 * @e_phnum: the number of programs
 *
 * Return: no return
 */
void print_numprograms(uint16_t e_phnum)
{
	printf("  Number of program headers:         ");
	printf("%u\n", (unsigned short)e_phnum);
}

/**
 * print_sectheadersize - prints the size of the sect headers
 * @e_shentsize: the size of the sect headers
 *
 * Return: no return
 */
void print_sectheadersize(uint16_t e_shentsize)
{
	printf("  Size of section headers:           ");
	printf("%u (bytes)\n", (unsigned short)e_shentsize);
}

/**
 * print_numsections - prints the number of sections
 * @e_shnum: the number of sections
 *
 * Return: no return
 */
void print_numsections(uint16_t e_shnum)
{
	printf("  Number of section headers:         ");
	printf("%u\n", (unsigned short)e_shnum);
}

/**
 * print_shstrndx - print index
 * @e_shstrndx: the index
 *
 * Return: no return
 */
void print_shstrndx(uint16_t e_shstrndx)
{
	printf("  Section header string table index: ");
	printf("%u\n", (unsigned short)e_shstrndx);
}
