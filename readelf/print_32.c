#include "readelf.h"

/**
 * print_elf32 - the main 32 print function
 *
 * Return: no return
 */
void print_elf32(void)
{
	printf("ELF Header:\n");
	print_magic(filestate.ehdr.ehdr32.e_ident);
	print_class(filestate.ehdr.ehdr32.e_ident);
	print_data(filestate.ehdr.ehdr32.e_ident);
	print_ident_version(filestate.ehdr.ehdr32.e_ident);
	print_abi(filestate.ehdr.ehdr32.e_ident);
	print_abi_ver(filestate.ehdr.ehdr32.e_ident);
	print_type(filestate.ehdr.ehdr32.e_type);
	print_machine(filestate.ehdr.ehdr32.e_machine);
	print_version(filestate.ehdr.ehdr32.e_version);
	print_entry64(filestate.ehdr.ehdr32.e_entry);
	print_progstart64(filestate.ehdr.ehdr32.e_phoff);
	print_sectstart64(filestate.ehdr.ehdr32.e_shoff);
	print_flags(filestate.ehdr.ehdr32.e_flags);
	print_headersize(filestate.ehdr.ehdr32.e_ehsize);
	print_progheadersize(filestate.ehdr.ehdr32.e_phentsize);
	print_numprograms(filestate.ehdr.ehdr32.e_phnum);
	print_sectheadersize(filestate.ehdr.ehdr32.e_shentsize);
	print_numsections(filestate.ehdr.ehdr32.e_shnum);
	print_shstrndx(filestate.ehdr.ehdr32.e_shstrndx);
}

/**
 * print_entry32 - print the entry address
 * @e_entry: the address
 *
 * Return: no return
 */
void print_entry32(Elf32_Addr e_entry)
{
	printf("  Entry point address:               ");
	printf("0x%x\n", (unsigned int)e_entry);
}

/**
 * print_progstart32 - prints the address of prog start
 * @e_phoff: the address in question
 *
 * Return: no return
 */
void print_progstart32(Elf32_Off e_phoff)
{
	printf("  Start of program headers:          ");
	printf("%u (bytes into file)\n", (unsigned int)e_phoff);
}

/**
 * print_sectstart32 - prints the address of the section start
 * @e_shoff: the address in question
 *
 * Return: no return
 */
void print_sectstart32(Elf32_Off e_shoff)
{
	printf("  Start of section headers:          ");
	printf("%u (bytes into file)\n", (unsigned int)e_shoff);
}
