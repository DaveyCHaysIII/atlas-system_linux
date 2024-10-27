#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  "HOLBERTON SCHOOL"
#define S3  "Holberton SchooL"
#define S4  "holberton"

void print_binary(int n);

void print_binary(int n) {
	long unsigned int i;
    unsigned int mask = 1 << (sizeof(n) * 8 - 1); // Mask with highest bit set
    for (i = 0; i < sizeof(n) * 8; i++) {
        putchar((n & mask) ? '1' : '0'); // Print 1 or 0 based on mask
        mask >>= 1; // Shift mask to the right
    }
    putchar('\n');
}

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	int result1 = strcasecmp(S1, S4);
	int result2 = asm_strcasecmp(S1, S4);
	print_binary(strcasecmp(S1, S4));
	print_binary(asm_strcasecmp(S1, S4));
	printf("strcasecmp(%s, %s) == %d\n", S1, S4, result1);
	printf("asm_strcasecmp(%s, %s) == %d\n", S1, S4, result2);
	printf("diff %d/%d: %d\n", result1, result2, (result1 - result2));
	printf("hex str/asm: %x/%x\n", result1, result2);
    assert(strcasecmp(S1, S1) == asm_strcasecmp(S1, S1));
    assert(strcasecmp(S1, S2) == asm_strcasecmp(S1, S2));
    assert(strcasecmp(S1, S3) == asm_strcasecmp(S1, S3));
    assert(strcasecmp(S1, S4) == asm_strcasecmp(S1, S4));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}
