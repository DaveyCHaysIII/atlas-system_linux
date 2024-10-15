#include "readelf.h"

void print_elf64()
{
	print_magic64(filestate.ehdr.ehdr64.e_ident);
	print_class64(filestate.ehdr.ehdr64.e_ident);
	print_data64(filestate.ehdr.ehdr64.e_ident);
	print_ident_version64(filestate.ehdr.ehdr64.e_ident);
	print_abi64(filestate.ehdr.ehdr64.e_ident);
	print_abi_ver64(filestate.ehdr.ehdr64.e_ident);
	print_type64(filestate.ehdr.ehdr64.e_type);
	print_machine64(filestate.ehdr.ehdr64.e_machine);
	print_version64(filestate.ehdr.ehdr64.e_version);
	print_entry64(filestate.ehdr.ehdr64.e_entry);
	print_progstart64(filestate.ehdr.ehdr64.e_phoff);
	print_sectstart64(filestate.ehdr.ehdr64.e_shoff);
	print_flags64(filestate.ehdr.ehdr64.e_flags);
	print_headersize64(filestate.ehdr.ehdr64.e_ehsize);
	print_progheadersize64(filestate.ehdr.ehdr64.e_phentsize);
	print_numprograms64(filestate.ehdr.ehdr64.e_phnum);
	print_sectheadersize64(filestate.ehdr.ehdr64.e_shentsize);
	print_numsections64(filestate.ehdr.ehdr64.e_shnum);
	print_shstrndx64(filestate.ehdr.ehdr64.e_shstrndx);
}

void print_magic64(unsigned char e_ident[EI_NIDENT])
{
}
