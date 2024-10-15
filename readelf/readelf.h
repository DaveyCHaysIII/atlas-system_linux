#ifndef READELF_MAIN
#define READELF_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

typedef struct Filestate
{
	char *program_name;
	char *exec_name;
	int fd;
	int endiFlag;
	union {
		Elf32_Ehdr ehdr32;
		Elf64_Ehdr ehdr64;
	} ehdr;
} Filestate;

extern Filestate filestate;
 
void init(int, char **);
int validate_header();

uint16_t swap_uint16(uint16_t);
uint32_t swap_uint32(uint32_t);
uint64_t swap_uint64(uint64_t);
void swap_all_endians32();
void swap_all_endians64();

/* 64 bit functions*/
void print_elf64();
void print_magic64(unsigned char e_ident[EI_NIDENT]);
void print_class64(unsigned char e_ident[EI_NIDENT]);
void print_data64(unsigned char e_ident[EI_NIDENT]);
void print_ident_version64(unsigned char e_ident[EI_NIDENT]);

void print_abi64(unsigned char e_ident[EI_NIDENT]);
void print_abi_ver64(unsigned char e_ident[EI_NIDENT]);
void print_type64(uint16_t e_type);
void print_machine64(uint16_t e_machine);
void print_version64(uint32_t e_version);

void print_entry64(Elf64_addr e_entry);
void print_progstart64(Elf64_Off e_phoff);
void print_sectstart64(Elf64_Off e_shoff);
void print_flags64(uint32_t e_flags);
void print_headersize64(uint16_t e_ehsize);

void print_progheadersize64(uint16_t e_phentsize);
void print_numprograms64(uint16_t e_phnum);
void print_sectheadersize64(uint16_t e_shentsize);
void print_numsections64(uint16_t e_shnum);
void print_shstrndx64(uint16_t e_shstrndx);

/* 32 bit functions*/
void print_elf32();
void print_magic32();
void print_class32();
void print_data32();
void print_ident_version32();

void print_abi32();
void print_abi_ver32();
void print_type32();
void print_machine32();
void print_version32();

void print_entry32();
void print_progstart32();
void print_sectstart32();
void print_flags64();
void print_headersize32();

void print_progheadersize32();
void print_numprograms64();
void print_sectheadersize32();
void print_numsections32();
void print_shstrndx32();

#endif
