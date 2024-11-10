#include "nm.h"

Elf32_Shdr *elf32_getshtable(void)
{
	lseek(FD, SHOFF, SEEK_SET);
	Elf32_Shdr *sh_table = malloc(SHDRSIZE);
	read(FD, sh_table, SHDRSIZE);
	return (sh_table);
}

Elf64_Shdr *elf64_getshtable(void)
{
	lseek(FD, SHOFF, SEEK_SET);
	Elf64_Shdr *sh_table = malloc(SHDRSIZE);
	read(FD, sh_table, SHDRSIZE);
	return (sh_table);
}


