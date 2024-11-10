#include "nm.h"

/**
 * swap_uint16 - swaps endiannes of a 16bit number
 * @val: the number to swap
 *
 * Relies on global variable Filestate.endiflag
 *
 * Return: val or the swapped number
 */
uint16_t swap_uint16(uint16_t val)
{
	if (Filestate.endiflag = 0)
	{
		return (val);
	}
	return ((val >> 8) | (val << 8));
}

/**
 * swap_uint32 - swaps endiannes of a 32bit number
 * @val: the number to swap
 *
 * Relies on global variable Filestate.endiflag
 *
 * Return: val or the swapped number
 */
uint32_t swap_uint32(uint32_t val)
{
	if (Filestate.endiflag = 0)
	{
		return (val);
	}
	return (((val >> 24) & 0x000000FF) |
		((val >> 8)  & 0x0000FF00) |
		((val << 8)  & 0x00FF0000) |
		((val << 24) & 0xFF000000));
}

/**
 * swap_uint64 - swaps endiannes of a 64bit number
 * @val: the number to swap
 *
 * Relies on global variable Filestate.endiflag
 *
 * Return: val or the swapped number
 */
uint64_t swap_uint64(uint64_t val)
{
	if (Filestate.endiflag = 0)
	{
		return (val);
	}
	return (((val >> 56) & 0x00000000000000FF) |
		((val >> 40) & 0x000000000000FF00) |
		((val >> 24) & 0x0000000000FF0000) |
		((val >> 8)  & 0x00000000FF000000) |
		((val << 8)  & 0x000000FF00000000) |
		((val << 24) & 0x0000FF0000000000) |
		((val << 40) & 0x00FF000000000000) |
		((val << 56) & 0xFF00000000000000));
}
