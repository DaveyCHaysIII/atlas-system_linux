#ifndef NM_MAIN
#define NM_MAIN

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

/* typedef */

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
	int endiflag;
	int eclass;
	char *strtable;
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

/* defines */
#define FD filestate.fd
#define ENDIFLAG filestate.endiflag
#define ECLASS filestate.eclass
#define SHOFF ((ECLASS == ELFCLASS32) ? filestate.ehdr.ehdr32.e_shoff : filestate.ehdr.ehdr64.e_shoff)
#define SHNUM ((ECLASS == ELFCLASS32) ? filestate.ehdr.ehdr32.e_shnum : filestate.ehdr.ehdr64.e_shnum)
#define SHENTSIZE ((ECLASS == ELFCLASS32) ? filestate.ehdr.ehdr32.e_shentsize : filestate.ehdr.ehdr64.e_shentsize)
#define SHDRSIZE (SHNUM * SHENTSIZE)
#define SHSTRNDX ((ECLASS == ELFCLASS32) ? filestate.ehdr.ehdr32.e_shstrndx : filestate.ehdr.ehdr64.e_shstrndx)
#define STRTAB filestate.strtable
/* init */
void error_handler(char *);
int validate_header(void);
void init(int, char **);
int main(int, char **);

/* symbolinit */
void elf32_symbolinit(void);
void elf64_symbolinit(void);
void print_symbols32(Elf32_Sym *, size_t, Elf32_Shdr *);
void print_symbols64(Elf64_Sym *, size_t, Elf64_Shdr *);

/* endian */
uint16_t swap_16(uint16_t);
uint32_t swap_32(uint32_t);
uint64_t swap_64(uint64_t);
void swap_ehdr(void);

#endif
