#include "readelf.h"

Filestate filestate;

int validate_header()
{

	int fd = filestate.fd;
	unsigned char e_ident[EI_NIDENT];

	if (read(fd, e_ident, EI_NIDENT) != EI_NIDENT)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

	if (e_ident[EI_MAG0] != ELFMAG0 || e_ident[EI_MAG1] != ELFMAG1 ||
		e_ident[EI_MAG2] != ELFMAG2 || e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "Not a valid ELF file\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
	
	if (e_ident[EI_DATA] == ELFDATA2LSB)
		filestate.endiFlag = 1;

	if (e_ident[EI_CLASS] == ELFCLASS32)
	{
		return (1);
	}
	else if (e_ident[EI_CLASS] == ELFCLASS64)
	{
		return (2);
	}
	else
	{
		fprintf(stderr, "something went wrong\n");
		close(fd);
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Must provide a file\n");
		exit(EXIT_FAILURE);
	}
	filestate.program_name = argv[0];
	filestate.exec_name = argv[1];
	filestate.endiflag = 0;
	filestate.fd = open(filestate.exec_name, O_RDONLY);
	if (filestate.fd == 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	int eclass = validate_header();
	if (eclass == 1)
	{
		read(filestate.fd, 
			&filestate.ehdr.ehdr32, sizeof(Elf32_Ehdr));
		if (filestate.endiFlag < 0)
			swap_all_endians32(filestate.ehdr.ehdr32);
		print_elf32(); 
	}
	else
	{
		read(filestate.fd, 
			&filestate.ehdr.ehdr64, sizeof(Elf64_Ehdr));
		if (filestate.endiFlag < 0)
			swap_all_endians64(filestate.ehdr.ehdr64);
		print_elf64();
	}
}


int main(int argc, char **argv)
{
	init(argc, argv);
	return (EXIT_SUCCESS);
}
