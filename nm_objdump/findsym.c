#include "nm.h"

int elf32_getshtable(void)
{
	int fd = filestate.fd;
	lseek(fd, filestate.ehdr.e_shoff, SEEK_SET);
	size_t sh_size = (filestate.ehdr.e_shentsize * filestate.ehdr.e_shnum);
	Elf32_Shdr *sh_table = malloc(sh_size);
	read(fd, shtable, sh_size);
	return (sh_table);
}

int elf64_getshtable(void)
{
	int fd = filestate.fd;
	lseek(fd, filestate.ehdr.e_shoff, SEEK_SET);
	size_t sh_size = (filestate.ehdr.e_shentsize * filestate.ehdr.e_shnum);
	Elf64_Shdr *sh_table = malloc(sh_size);
	read(fd, shtable, sh_size);
	return (sh_table);
}


