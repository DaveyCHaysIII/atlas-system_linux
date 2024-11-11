#include "nm.h"


/**
 * elf32_symbolinit - initializes section part of program
 *
 * Return: no return
 */
void elf32_symbolinit(void)
{
	printf("Got to symbol init!\n");
	lseek(FD, SHOFF, SEEK_SET);
	Elf32_Shdr *shdrs = malloc(SHDRSIZE);
	read(FD, shdrs, SHDRSIZE);

	uint32_t shstr_offset = shdrs[SHSTRNDX].sh_offset;
	uint32_t shstr_size = shdrs[SHSTRNDX].sh_size;

	lseek(FD, swap_32(shstr_offset), SEEK_SET);
	char *sstr_table = malloc(swap_32(shstr_size));
	read(FD, sstr_table, shstr_size);

	Elf32_Sym *symtab = NULL;
	Elf32_Sym *dynsym = NULL;
	size_t symtab_numsymbols = 0;
	/*size_t dynsym_numsymbols = 0;*/

	for (int i = 0; i < SHNUM; i++)
	{
		char *sh_name = sstr_table + swap_32(shdrs[i].sh_name);
		if (strcmp(sh_name, ".symtab") == 0)
		{
			symtab = malloc(swap_32(shdrs[i].sh_size));
			lseek(FD, swap_32(shdrs[i].sh_offset), SEEK_SET);
			read(FD, symtab, swap_32(shdrs[i].sh_size));
			symtab_numsymbols = (swap_32(shdrs[i].sh_size) / sizeof(Elf32_Sym));
			printf("num symbols: %lu\n", symtab_numsymbols);
		}
	/*	else if (strcmp(sh_name, ".dynsym") == 0)
		{
			dynsym = malloc(swap_32(shdrs[i].sh_size));
			lseek(FD, swap_32(shdrs[i].sh_offset), SEEK_SET);
			read(FD, dynsym, swap_32(shdrs[i].sh_size));
			dynsym_numsymbols = (swap_32(shdrs[i].sh_size) / sizeof(Elf32_Sym));
		}*/
		else if (strcmp(sh_name, ".strtab") == 0)
		{
			filestate.strtable = malloc(swap_32(shdrs[i].sh_size));
			lseek(FD, swap_32(shdrs[i].sh_offset), SEEK_SET);
			read(FD, filestate.strtable, swap_32(shdrs[i].sh_size));
		}
	}
	if (symtab != NULL)
	{
		print_symbols32(symtab, symtab_numsymbols);
		free(symtab);
	}
	if (dynsym != NULL)
	{
		/*print_symbols32(dynsym, dynsym_numsymbols);*/
		free(dynsym);
	}
	free(shdrs);
	free(sstr_table);
	free(filestate.strtable);
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

void print_symbols32(Elf32_Sym *symbols, size_t numsymbols)
{
	for (size_t i = 0; i < numsymbols; i++)
	{
		Elf32_Sym *sym = &symbols[i];

		char *symbol_name = STRTAB + swap_32(sym->st_name);
		if (symbol_name == NULL || *symbol_name == '\0')
			continue;
		unsigned char type = sym->st_info & 0x0f;
		char typechar = '?';

		switch (type)
		{
			case 0x01: typechar = 'T'; break;
			case 0x02: typechar = 'T'; break;
			case 0x03: typechar = 'B'; break;
			case 0x0e: typechar = 'U'; break;
			case 0x0f: typechar = 'L'; break;
			case 0x10: typechar = 'C'; break;
			default: typechar = '?'; break;
		}
		if (sym->st_value == 0)
			printf("         U %s\n", symbol_name);
		else
			printf("%08" PRIx32 " %c %s %d\n", sym->st_value, typechar, symbol_name, type);
	}
}




