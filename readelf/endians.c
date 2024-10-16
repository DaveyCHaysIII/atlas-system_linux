#include "readelf.h"

/**
 * swap_uint16 - swaps endiannes of a 16bit number
 * @val: the number to swap
 *
 * Return: the swapped number
 */
uint16_t swap_uint16(uint16_t val)
{
	return ((val >> 8) | (val << 8));
}

/**
 * swap_uint32 - swaps endiannes of a 32bit number
 * @val: the number to swap
 *
 * Return: the swapped number
 */
uint32_t swap_uint32(uint32_t val)
{
	return (((val >> 24) & 0x000000FF) |
		((val >> 8)  & 0x0000FF00) |
		((val << 8)  & 0x00FF0000) |
		((val << 24) & 0xFF000000));
}

/**
 * swap_uint64 - swaps endiannes of a 64bit number
 * @val: the number to swap
 *
 * Return: the swapped number
 */
uint64_t swap_uint64(uint64_t val)
{
	return (((val >> 56) & 0x00000000000000FF) |
		((val >> 40) & 0x000000000000FF00) |
		((val >> 24) & 0x0000000000FF0000) |
		((val >> 8)  & 0x00000000FF000000) |
		((val << 8)  & 0x000000FF00000000) |
		((val << 24) & 0x0000FF0000000000) |
		((val << 40) & 0x00FF000000000000) |
		((val << 56) & 0xFF00000000000000));
}

/**
 * swap_all_endians32 - swaps endiannes of all multi-byte entries
 *
 * Return: No return
 */
void swap_all_endians32(void)
{
	uint16_t type = filestate.ehdr.ehdr32.e_type;
	uint16_t machine = filestate.ehdr.ehdr32.e_machine;
	uint32_t version = filestate.ehdr.ehdr32.e_version;
	uint32_t entry = filestate.ehdr.ehdr32.e_entry;
	uint32_t phoff = filestate.ehdr.ehdr32.e_phoff;
	uint32_t shoff = filestate.ehdr.ehdr32.e_shoff;
	uint32_t flags = filestate.ehdr.ehdr32.e_flags;
	uint16_t hsize = filestate.ehdr.ehdr32.e_ehsize;
	uint16_t phentsize = filestate.ehdr.ehdr32.e_phentsize;
	uint16_t phnum = filestate.ehdr.ehdr32.e_phnum;
	uint16_t shentsize = filestate.ehdr.ehdr32.e_shentsize;
	uint16_t shnum = filestate.ehdr.ehdr32.e_shnum;
	uint16_t shstrndx = filestate.ehdr.ehdr32.e_shstrndx;

	filestate.ehdr.ehdr32.e_type = swap_uint16(type);
	filestate.ehdr.ehdr32.e_machine = swap_uint16(machine);
	filestate.ehdr.ehdr32.e_version = swap_uint32(version);
	filestate.ehdr.ehdr32.e_entry = swap_uint32(entry);
	filestate.ehdr.ehdr32.e_phoff = swap_uint32(phoff);
	filestate.ehdr.ehdr32.e_shoff = swap_uint32(shoff);
	filestate.ehdr.ehdr32.e_flags = swap_uint32(flags);
	filestate.ehdr.ehdr32.e_ehsize = swap_uint16(hsize);
	filestate.ehdr.ehdr32.e_phentsize = swap_uint16(phentsize);
	filestate.ehdr.ehdr32.e_phnum = swap_uint16(phnum);
	filestate.ehdr.ehdr32.e_shentsize = swap_uint16(shentsize);
	filestate.ehdr.ehdr32.e_shnum = swap_uint16(shnum);
	filestate.ehdr.ehdr32.e_shstrndx = swap_uint16(shstrndx);
}

/**
 * swap_all_endians64 - swaps endiannes of all multi-byte entries
 *
 * Return: No return
 */
void swap_all_endians64(void)
{
	uint16_t type = filestate.ehdr.ehdr64.e_type;
	uint16_t machine = filestate.ehdr.ehdr64.e_machine;
	uint32_t version = filestate.ehdr.ehdr64.e_version;
	uint64_t entry = filestate.ehdr.ehdr64.e_entry;
	uint64_t phoff = filestate.ehdr.ehdr64.e_phoff;
	uint64_t shoff = filestate.ehdr.ehdr64.e_shoff;
	uint32_t flags = filestate.ehdr.ehdr64.e_flags;
	uint16_t hsize = filestate.ehdr.ehdr64.e_ehsize;
	uint16_t phentsize = filestate.ehdr.ehdr64.e_phentsize;
	uint16_t phnum = filestate.ehdr.ehdr64.e_phnum;
	uint16_t shentsize = filestate.ehdr.ehdr64.e_shentsize;
	uint16_t shnum = filestate.ehdr.ehdr64.e_shnum;
	uint16_t shstrndx = filestate.ehdr.ehdr64.e_shstrndx;

	filestate.ehdr.ehdr64.e_type = swap_uint16(type);
	filestate.ehdr.ehdr64.e_machine = swap_uint16(machine);
	filestate.ehdr.ehdr64.e_version = swap_uint32(version);
	filestate.ehdr.ehdr64.e_entry = swap_uint64(entry);
	filestate.ehdr.ehdr64.e_phoff = swap_uint64(phoff);
	filestate.ehdr.ehdr64.e_shoff = swap_uint64(shoff);
	filestate.ehdr.ehdr64.e_flags = swap_uint32(flags);
	filestate.ehdr.ehdr64.e_ehsize = swap_uint16(hsize);
	filestate.ehdr.ehdr64.e_phentsize = swap_uint16(phentsize);
	filestate.ehdr.ehdr64.e_phnum = swap_uint16(phnum);
	filestate.ehdr.ehdr64.e_shentsize = swap_uint16(shentsize);
	filestate.ehdr.ehdr64.e_shnum = swap_uint16(shnum);
	filestate.ehdr.ehdr64.e_shstrndx = swap_uint16(shstrndx);
}
