#include "0-hreadelf.h"

void print_header(const char *file)
{
	int fd = open(file, O_RDONLY);
	if (fd == 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}

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

	if (e_ident[EI_CLASS] == ELFCLASS32)
	{
		printf("This is a 32 bit system\n");
	}
	else if (e_ident[EI_CLASS] == ELFCLASS64)
	{
		printf("This is a 64 bit system\n");
	}
	else
	{
		fprintf(stderr, "something went wrong\n");
	}
	close(fd);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Must provide a file dummy!\n");
		return (EXIT_FAILURE);
	}
	print_header(argv[1]);
	return (EXIT_SUCCESS);
}
