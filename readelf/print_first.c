#include "readelf.h"

/**
 * print_magic - prints the magic number
 * @e_ident: the magic number to print
 *
 * Return: no return
 */
void print_magic(unsigned char e_ident[EI_NIDENT])
{
	printf("  Magic:   ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", e_ident[i]);
	printf("\n");
}

/**
 * print_class - prints the class
 * @e_ident: the first line of the header
 *
 * Return: no return
 */
void print_class(unsigned char e_ident[EI_NIDENT])
{
	if (e_ident[EI_CLASS] == ELFCLASS64)
		printf("  Class:                             ELF64\n");
	else
		printf("  Class:                             ELF32\n");
}

/**
 * print_data - prints the endian class of the header
 * @e_ident: the first line of the header
 *
 * Return: no return
 */
void print_data(unsigned char e_ident[EI_NIDENT])
{
	printf("  Data:                              ");
	if (e_ident[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little-endian\n");
	else if (e_ident[EI_DATA] == ELFDATA2MSB)
		printf("2's complement, big-endian\n");
	else
		printf("Invalid data encoding\n");
}

/**
 * print_ident_version - prints the ident version
 * @e_ident: the first line of the header
 *
 * Return: no return
 */
void print_ident_version(unsigned char e_ident[EI_NIDENT])
{
	if (e_ident[EI_VERSION] == EV_CURRENT)
		printf("  Version:                           1 (current)\n");
	else
		printf("  Version:                         Invalid Version\n");
}
