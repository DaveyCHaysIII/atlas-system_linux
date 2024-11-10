#ifndef NM_MAIN
#define NM_MAIN

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <stderr.h>
#include <elf.h>
#include <fnctl.h>
#include <unistd.h>

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

/* init */
void error_handler(char *);
int validate_header(void);
void init(int, char **);
int main(int, char **);

/* findsym */
int elf32_getshtable(void);
int elf64_getshtable(void);

/* endian */
uint16_t swap_uint16(uint16_t);
uint32_t swap_uint32(uint32_t);
uint64_t swap_uint64(uint64_t);

#endif
