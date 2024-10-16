#include "readelf.h"

/**
 * print_abi - prints the abi
 * @e_ident: the first line of the header
 *
 * Return: no return
 */
void print_abi(unsigned char e_ident[EI_NIDENT])
{
	printf("  OS/ABI:                            ");
	switch (e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_HPUX:
		printf("HP-UX\n");
		break;
	case ELFOSABI_NETBSD:
		printf("NetBSD\n");
		break;
	case ELFOSABI_LINUX:
		printf("Linux\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("Solaris\n");
		break;
	case ELFOSABI_AIX:
		printf("AIX\n");
		break;
	case ELFOSABI_IRIX:
		printf("IRIX\n");
		break;
	case ELFOSABI_FREEBSD:
		printf("FreeBSD\n");
		break;
	case ELFOSABI_TRU64:
		printf("TRU64\n");
		break;
	case ELFOSABI_ARM:
		printf("ARM architecture\n");
		break;
	case ELFOSABI_STANDALONE:
		printf("Standalone (embedded) application\n");
		break;
	default:
		printf("Unknown (0x%x)\n", e_ident[EI_OSABI]);
		break;
	}
}

/**
 * print_abi_ver - prints the abi version
 *
 * Return: no return
 */
void print_abi_ver(void)
{
	printf("  ABI Version:                       0\n");
}

/**
 * print_type - prints the type
 * @e_type: the type to print
 *
 * Return: no return
 */
void print_type(uint16_t e_type)
{
	printf("  Type:                              ");
	switch (e_type)
	{
	case ET_NONE:
		printf("No file type\n");
		break;
	case ET_REL:
		printf("Relocatable file\n");
		break;
	case ET_EXEC:
		printf("Executable file\n");
		break;
	case ET_DYN:
		printf("DYN (Position-Independant Executable file)\n");
		break;
	case ET_CORE:
		printf("Core file\n");
		break;
	default:
		printf("Unknown (0x%x)\n", e_type);
		break;
	}
}

/**
 * print_machine - prints the machine
 * @e_machine: the machine to print
 *
 * Return: no return
 */
void print_machine(uint16_t e_machine)
{
	printf("  Machine:                           ");
	machine_print_first(e_machine);
}

/**
 * print_version - prints the version
 * @e_version: the version to print
 *
 * Return: no retrun
 */
void print_version(uint32_t e_version)
{
	printf("  Version:                           ");
	printf("%u\n", (unsigned int)e_version);
}
