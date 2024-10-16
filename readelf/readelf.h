#ifndef READELF_MAIN
#define READELF_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

/**
 * struct Filestate - carries state information of header
 * @program_name: the name of this program
 * @exec_name: name of executable passed
 * @fd: the open file descriptor
 * @endiFlag: flag for endiannes
 * @ehdr: the header in question
 */
typedef struct Filestate
{
	char *program_name;
	char *exec_name;
	int fd;
	int endiFlag;
	/**
	 * union ehdr - holds the union
	 */
	union
	{
		Elf32_Ehdr ehdr32;
		Elf64_Ehdr ehdr64;
	} ehdr;
} Filestate;

extern Filestate filestate;

void init(int, char **);
int validate_header(void);

uint16_t swap_uint16(uint16_t);
uint32_t swap_uint32(uint32_t);
uint64_t swap_uint64(uint64_t);
void swap_all_endians32(void);
void swap_all_endians64(void);

/* 64 bit functions*/

/* PRINT_64.C */
void print_elf64(void);
void print_entry64(Elf64_Addr e_entry);
void print_progstart64(Elf64_Off e_phoff);
void print_sectstart64(Elf64_Off e_shoff);

/* 32 bit functions*/

/* PRINT_32.C */
void print_elf32(void);
void print_entry32(Elf32_Addr e_entry);
void print_progstart32(Elf32_Off e_phoff);
void print_sectstart32(Elf32_Off e_shoff);

/* Generic Functions*/

/* PRINT_FIRST.C */
void print_magic(unsigned char e_ident[EI_NIDENT]);
void print_class(unsigned char e_ident[EI_NIDENT]);
void print_data(unsigned char e_ident[EI_NIDENT]);
void print_ident_version(unsigned char e_ident[EI_NIDENT]);

/* PRINT_SECOND.C */
void print_abi(unsigned char e_ident[EI_NIDENT]);
void print_abi_ver(void);
void print_type(uint16_t e_type);
void print_machine(uint16_t e_machine);
void print_version(uint32_t e_version);

/* PRINT_THIRD.C */
void print_flags(void);
void print_headersize(uint16_t e_ehsize);

/* PRINT_FOURTH.C */
void print_progheadersize(uint16_t e_phentsize);
void print_numprograms(uint16_t e_phnum);
void print_sectheadersize(uint16_t e_shentsize);
void print_numsections(uint16_t e_shnum);
void print_shstrndx(uint16_t e_shstrndx);

/* MACHINE.C*/
void machine_print_first(uint16_t e_machine);
void machine_print_second(uint16_t e_machine);

#endif
