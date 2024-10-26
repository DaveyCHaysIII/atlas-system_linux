#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "libasm.h"

#define S1  "Holberton School"
#define S2  ""
#define S3  "Holberton Socool"

/**
 * main - Program entry point
 *
 * Return: EXIT_SUCCESS or EXIT_FAILURE
 */
int main(void)
{
	char *S4 = "Holberton";
	printf("strncmp(%s, %s, %lu) == %d\n", S1, S4, strlen(S2), strncmp(S1, S4, strlen(S2)));
	printf("asm_strncmp(%s, %s, %lu) == %d\n", S1, S4, strlen(S2), asm_strncmp(S1, S4, strlen(S2)));
    assert(strncmp(S1, S3, 1) == asm_strncmp(S1, S3, 1));
    assert(strncmp(S1, S3, 11) == asm_strncmp(S1, S3, 11));
    assert(strncmp(S1, S3, 15) == asm_strncmp(S1, S3, 15));

    printf("All good!\n");
    return (EXIT_SUCCESS);
}
