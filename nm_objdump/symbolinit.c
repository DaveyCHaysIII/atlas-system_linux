#include "nm.h"


/**
 * elf32_symbolinit - initializes section part of program
 *
 * Return: no return
 */
void elf32_symbolinit(void)
{
	lseek(FD, SHOFF, SEEK_SET);
	Elf32_Shdr *shdrs = malloc(SHDRSIZE);
	read(FD, shdrs, SHDRSIZE);

	uint32_t shstr_offset = shdrs[SHSTRNDX].sh_offset;
	uint32_t shstr_size = shdrs[SHSTRNDX].sh_size;

	lseek(FD, swap_32(shstr_offset), SEEK_SET);
	char *sstr_table = malloc(swap_32(shstr_size));
	read(FD, sstr_table, shstr_size);

	printf("eclass: %u\n", ECLASS);

	for (int i = 0; i < SHNUM; i++)
	{
		char *sh_name = sstr_table + swap_32(shdrs[i].sh_name);
		printf("Section Header: %s\n", sh_name);
	}
	free(shdrs);
	free(sstr_table);
}

/**
 * elf64_symbolinit - initializes section part of program
 *
 * Return: no return
 */
void elf64_symbolinit(void)
{
	lseek(FD, SHOFF, SEEK_SET);
	Elf64_Shdr *shdrs = malloc(SHDRSIZE);
	read(FD, shdrs, SHDRSIZE);

	uint64_t shstr_offset = shdrs[SHSTRNDX].sh_offset;
	uint64_t shstr_size = shdrs[SHSTRNDX].sh_size;

	lseek(FD, swap_64(shstr_offset), SEEK_SET);
	char *sstr_table = malloc(swap_32(shstr_size));
	read(FD, sstr_table, shstr_size);

	for (int i = 0; i < SHNUM; i++)
	{
		char *sh_name = sstr_table + swap_32(shdrs[i].sh_name);
		printf("Section Header: %s\n", sh_name);
	}
	free(shdrs);
	free(sstr_table);
}
