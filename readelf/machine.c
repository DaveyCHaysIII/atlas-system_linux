#include "readelf.h"

/**
 * machine_print_first - first half of switch for machine
 * @e_machine: the machine descriptor
 *
 * Return: no return
 */
void machine_print_first(uint16_t e_machine)
{
	switch (e_machine)
	{
	case EM_M32:
		printf("AT&T WE 32100\n");
		break;
	case EM_SPARC:
		printf("Sun Microsystems SPARC\n");
		break;
	case EM_386:
		printf("Intel 80386\n");
		break;
	case EM_68K:
		printf("Motorola 68000\n");
		break;
	case EM_88K:
		printf("Motorola 88000\n");
		break;
	case EM_860:
		printf("Intel 80860\n");
		break;
	case EM_MIPS:
		printf("MIPS RS3000\n");
		break;
	case EM_PARISC:
		printf("HP/PA\n");
		break;
	case EM_SPARC32PLUS:
		printf("SPARC with enhanced instruction set");
		break;
	case EM_PPC:
		printf("PowerPC\n");
		break;
	default:
		machine_print_second(e_machine);
		break;
	}
}

/**
 * machine_print_second - second half of switch for machine
 * @e_machine: the machine descriptor
 *
 * Return: no retrun
 */
void machine_print_second(uint16_t e_machine)
{
	switch (e_machine)
	{
	case EM_PPC64:
		printf("PowerPC 64-bit\n");
		break;
	case EM_S390:
		printf("IBM S/390\n");
		break;
	case EM_ARM:
		printf("Advanced RISC Machines\n");
		break;
	case EM_SH:
		printf("Renesas SuperH\n");
		break;
	case EM_SPARCV9:
		printf("SPARC v9 64-bit\n");
		break;
	case EM_IA_64:
		printf("Intel Itanium\n");
		break;
	case EM_X86_64:
		printf("Advanced Micro Devices x86-64\n");
		break;
	case EM_VAX:
		printf("DEC Vax\n");
		break;
	default:
		printf("An Unknown Machine\n");
		break;
	}
}
