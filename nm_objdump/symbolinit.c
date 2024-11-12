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

	Elf32_Sym *symtab = NULL;
	size_t symtab_numsymbols = 0;

	for (int i = 0; i < SHNUM; i++)
	{
		char *sh_name = sstr_table + swap_32(shdrs[i].sh_name);
		if (strcmp(sh_name, ".symtab") == 0)
		{
			symtab = malloc(swap_32(shdrs[i].sh_size));
			lseek(FD, swap_32(shdrs[i].sh_offset), SEEK_SET);
			read(FD, symtab, swap_32(shdrs[i].sh_size));
			symtab_numsymbols = (swap_32(shdrs[i].sh_size) / sizeof(Elf32_Sym));
		}
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
	char *sstr_table = malloc(swap_64(shstr_size));
	read(FD, sstr_table, shstr_size);

	Elf64_Sym *symtab = NULL;
	size_t symtab_numsymbols = 0;

	for (int i = 0; i < SHNUM; i++)
	{
		char *sh_name = sstr_table + swap_32(shdrs[i].sh_name);
		if (strcmp(sh_name, ".symtab") == 0)
		{
			symtab = malloc(swap_64(shdrs[i].sh_size));
			lseek(FD, swap_64(shdrs[i].sh_offset), SEEK_SET);
			read(FD, symtab, swap_64(shdrs[i].sh_size));
			symtab_numsymbols = (swap_64(shdrs[i].sh_size) / sizeof(Elf64_Sym));
		}
		else if (strcmp(sh_name, ".strtab") == 0)
		{
			filestate.strtable = malloc(swap_64(shdrs[i].sh_size));
			lseek(FD, swap_64(shdrs[i].sh_offset), SEEK_SET);
			read(FD, filestate.strtable, swap_64(shdrs[i].sh_size));
		}
	}
	if (symtab != NULL)
	{
		print_symbols64(symtab, symtab_numsymbols);
		free(symtab);
	}
	free(shdrs);
	free(sstr_table);
	free(filestate.strtable);

}

/**
 * print_symbols32 - prints the symbols
 * @symbols: the symbol table to pull the symbols from
 * @numsymbols: supposedly the number of symbols to write
 *
 * Return: no return
 */
void print_symbols32(Elf32_Sym *symbols, size_t numsymbols)
{
	for (size_t i = 0; i < numsymbols; i++)
	{
		Elf32_Sym *sym = &symbols[i];

		char *symbol_name = STRTAB + swap_32(sym->st_name);
		if (symbol_name == NULL || *symbol_name == '\0')
			continue;
		unsigned char type = ELF32_ST_TYPE(sym->st_info);
		unsigned char bind = ELF32_ST_BIND(sym->st_info);
		uint16_t shndx = swap_16(sym->st_shndx);
		char typechar = '?';

		if (shndx == SHN_UNDEF)
			typechar = 'U';
		if (sym->st_value == 0)
			continue;
	/*		printf("         U %s\n", symbol_name); */
		else
			printf("%08" PRIx32 " %c %s %d, %d, %hu\n", sym->st_value, typechar, symbol_name, type, bind, shndx);
	}
}

/**
 * print_symbols64 - prints the symbols
 * @symbols: the symbol table to pull the symbols from
 * @numsymbols: supposedly the number of symbols to write
 *
 * Return: no return
 */
void print_symbols64(Elf64_Sym *symbols, size_t numsymbols)
{
	for (size_t i = 0; i < numsymbols; i++)
	{
		Elf64_Sym *sym = &symbols[i];

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
			continue;
		/*	printf("                 U %s\n", symbol_name); */
		else
			printf("%016" PRIx64 " %c %s %d\n", sym->st_value, typechar, symbol_name, type);
	}
}

