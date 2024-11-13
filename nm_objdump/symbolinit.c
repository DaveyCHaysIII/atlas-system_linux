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
	if (symtab == NULL)
	{
		printf("nm: %s: no symbols\n", filestate.exec_name);
	}
	else
	{
		print_symbols32(symtab, symtab_numsymbols, shdrs);
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
	if (symtab == NULL)
	{
		printf("nm: %s: no symbols\n", filestate.exec_name);
	}
	else
	{
		print_symbols64(symtab, symtab_numsymbols, shdrs);
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
void print_symbols32(Elf32_Sym *symbols, size_t numsymbols, Elf32_Shdr *shdrs)
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

		if (shndx < SHNUM && shndx != SHN_ABS && shndx != SHN_COMMON)
		{
			swap_32(shdrs[shndx].sh_type);
			swap_32(shdrs[shndx].sh_flags);
		}

		char typechar = '?';
		if (type == STT_FILE)
			continue;

		if (bind == STB_GNU_UNIQUE)
		{
			typechar = 'u';
		}
		else if (bind == STB_WEAK && type == STT_OBJECT)
		{
			if (shndx == SHN_UNDEF)
			{
				typechar = 'v';
			}
			else
			{
				typechar = 'V';
			}
		}
		else if (bind == STB_WEAK)
		{
			if (shndx == SHN_UNDEF)
			{
				typechar = 'w';
			}
			else
				typechar = 'W';
		}
		else if (shndx == SHN_UNDEF)
		{
			typechar = 'U';
		}
		else if (shndx == SHN_ABS)
		{
			typechar = 'A';
		}
		else if (shndx == SHN_COMMON)
		{
			typechar = 'C';
		}
		else if (shdrs[shndx].sh_type == SHT_NOBITS &&
			shdrs[shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			typechar = 'B';
		else if (shdrs[shndx].sh_type == SHT_PROGBITS &&
			shdrs[shndx].sh_flags == SHF_ALLOC)
			typechar = 'R';
		else if (shdrs[shndx].sh_type == SHT_PROGBITS &&
			shdrs[shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			typechar = 'D';
		else if (shdrs[shndx].sh_type == SHT_PROGBITS &&
			shdrs[shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			typechar = 'T';
		else if (shdrs[shndx].sh_type == SHT_DYNAMIC)
			typechar = 'D';
		else
			typechar = 'T';

		if (bind == STB_LOCAL && typechar != '?')
			typechar += 32;

		if (typechar == 'U')
		{
			printf("         U %s\n", symbol_name);
			continue;
		}

		printf("%08" PRIx32 " %c %s\n", sym->st_value, typechar, symbol_name);
	}
}

/**
 * print_symbols64 - prints the symbols
 * @symbols: the symbol table to pull the symbols from
 * @numsymbols: supposedly the number of symbols to write
 *
 * Return: no return
 */
void print_symbols64(Elf64_Sym *symbols, size_t numsymbols, Elf64_Shdr *shdrs)
{
	for (size_t i = 0; i < numsymbols; i++)
	{
		Elf64_Sym *sym = &symbols[i];

		char *symbol_name = STRTAB + swap_32(sym->st_name);
		if (symbol_name == NULL || *symbol_name == '\0')
			continue;
		unsigned char type = ELF64_ST_TYPE(sym->st_info);
		unsigned char bind = ELF64_ST_BIND(sym->st_info);
		uint16_t shndx = swap_16(sym->st_shndx);

		if (shndx < SHNUM && shndx != SHN_ABS && shndx != SHN_COMMON)
		{
			swap_32(shdrs[shndx].sh_type);
			swap_64(shdrs[shndx].sh_flags);
		}

		char typechar = '?';
		if (type == STT_FILE)
			continue;

		if (bind == STB_GNU_UNIQUE)
		{
			typechar = 'u';
		}
		else if (bind == STB_WEAK && type == STT_OBJECT)
		{
			if (shndx == SHN_UNDEF)
			{
				typechar = 'v';
			}
			else
			{
				typechar = 'V';
			}
		}
		else if (bind == STB_WEAK)
		{
			if (shndx == SHN_UNDEF)
			{
				typechar = 'w';
			}
			else
				typechar = 'W';
		}
		else if (shndx == SHN_UNDEF)
		{
			typechar = 'U';
		}
		else if (shndx == SHN_ABS)
		{
			typechar = 'A';
		}
		else if (shndx == SHN_COMMON)
		{
			typechar = 'C';
		}
		else if (shdrs[shndx].sh_type == SHT_NOBITS &&
			shdrs[shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			typechar = 'B';
		else if (shdrs[shndx].sh_type == SHT_PROGBITS &&
			shdrs[shndx].sh_flags == SHF_ALLOC)
			typechar = 'R';
		else if (shdrs[shndx].sh_type == SHT_PROGBITS &&
			shdrs[shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			typechar = 'D';
		else if (shdrs[shndx].sh_type == SHT_PROGBITS &&
			shdrs[shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
			typechar = 'T';
		else if (shdrs[shndx].sh_type == SHT_DYNAMIC)
			typechar = 'D';
		else
			typechar = 'T';

		if (bind == STB_LOCAL && typechar != '?')
		{
			typechar += 32;
		}
		if (typechar == 'U')
		{
			printf("                 U %s\n", symbol_name);
			continue;
		}

		printf("%016" PRIx64 " %c %s\n", sym->st_value, typechar, symbol_name);
	}
}

