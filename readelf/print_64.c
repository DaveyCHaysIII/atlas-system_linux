#include "readelf.h"

/**
 * print_elf64 - the main 64 print function
 *
 * Return: no return
 */
void print_elf64(void)
{
	printf("ELF Header:\n");
	print_magic(filestate.ehdr.ehdr64.e_ident);
	print_class(filestate.ehdr.ehdr64.e_ident);
	print_data(filestate.ehdr.ehdr64.e_ident);
	print_ident_version(filestate.ehdr.ehdr64.e_ident);
	print_abi(filestate.ehdr.ehdr64.e_ident);
	print_abi_ver(filestate.ehdr.ehdr64.e_ident);
	print_type(filestate.ehdr.ehdr64.e_type);
	print_machine(filestate.ehdr.ehdr64.e_machine);
	print_version(filestate.ehdr.ehdr64.e_version);
	print_entry64(filestate.ehdr.ehdr64.e_entry);
	print_progstart64(filestate.ehdr.ehdr64.e_phoff);
	print_sectstart64(filestate.ehdr.ehdr64.e_shoff);
	print_flags();
	print_headersize(filestate.ehdr.ehdr64.e_ehsize);
	print_progheadersize(filestate.ehdr.ehdr64.e_phentsize);
	print_numprograms(filestate.ehdr.ehdr64.e_phnum);
	print_sectheadersize(filestate.ehdr.ehdr64.e_shentsize);
	print_numsections(filestate.ehdr.ehdr64.e_shnum);
	print_shstrndx(filestate.ehdr.ehdr64.e_shstrndx);
}

/**
 * print_entry64 - print the entry address
 * @e_entry: the address
 *
 * Return: no return
 */
void print_entry64(Elf64_Addr e_entry)
{
	printf("  Entry point address:               ");
	printf("0x%lx\n", (unsigned long)e_entry);
}

/**
 * print_progstart64 - prints the address of prog start
 * @e_phoff: the address in question
 *
 * Return: no return
 */
void print_progstart64(Elf64_Off e_phoff)
{
	printf("  Start of program headers:          ");
	printf("%lu (bytes into file)\n", (unsigned long)e_phoff);
}

/**
 * print_sectstart64 - prints the address of the section start
 * @e_shoff: the address in question
 *
 * Return: no return
 */
void print_sectstart64(Elf64_Off e_shoff)
{
	printf("  Start of section headers:          ");
	printf("%lu (bytes into file)\n", (unsigned long)e_shoff);
}
