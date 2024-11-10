#include <nm.h>

Filestate filestate;

/**
 * error_handler - handles errors
 * @error: the error to handle
 *
 * Return: no retrun
 */
void error_handler(char *error)
{
	fprintf(stderr, "%s: %s: %s\n",
			filestate.program_name,
			filestate.exec_name,
			error);

	if (fcntl(filestate.fd, F_GETFD) != -1)
	{
		close(filestate.fd);
	}
	exit(EXIT_FAILURE);
}

/**
 * validate_header - valdiates the header
 *
 * Return: no return
 */
int validate_header(void)
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
		filestate.endiflag = 1;

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

/**
 * init - initializes the program
 * @argc: number of args passed
 * @argv: arg vector
 *
 * Return: no return
 */
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
	filestate.eclass = validate_header();

	lseek(filestate.fd, 0, SEEK_SET);
	if (filestate.eclass == 1)
	{
		read(filestate.fd,
			&filestate.ehdr.ehdr32, sizeof(Elf32_Ehdr));
		elf32_findsymtable();
	}
	else
	{
		read(filestate.fd,
			&filestate.ehdr.ehdr64, sizeof(Elf64_Ehdr));
		elf64_findsymtable();
	}
}

/**
 * main - entry point of program
 * @argc: number of args
 * @argv: argument vector
 *
 * Return: 0 or 1
 */

int main(int argc, char **argv)
{
	init(int argc, char **argv);
	return (EXIT_SUCCESS);
}
