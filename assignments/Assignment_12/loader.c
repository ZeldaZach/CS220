#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define FILE_SIZE 99 /* Size of func.bin */

int main(int argc, char *argv[])
{
	FILE *fp;
	unsigned int num1, num2, result;
	unsigned char *raw_bytes, operation;
	typedef int (*Calc_fptr)(char, int, int);
	Calc_fptr calculator;

	if (argc != 5)
	{
		printf("Usage %s <filename><uint><operation><uint>\n", argv[0]);
		exit(1);
	}

	/* Open/read binary file */
	fp = fopen(argv[1], "rb");
	
	if (!fp)
	{
		printf("File not found\n");
		exit(1);
	}

	/* Malloc for raw_bytes */
	raw_bytes = malloc(FILE_SIZE);
	mprotect(raw_bytes, FILE_SIZE, PROT_EXEC);
	mprotect(raw_bytes, FILE_SIZE, PROT_READ);
	mprotect(raw_bytes, FILE_SIZE, PROT_WRITE);

	/* Read file into buffer */
	fread(raw_bytes, FILE_SIZE, 1, fp);

	/* Cast args appropriately */
	num1 = atoi(argv[2]);
	num2 = atoi(argv[4]);
	operation = *argv[3];

	/* Cast buffer to the calculator() func */
	calculator = (Calc_fptr)raw_bytes;
	
	/* Print results */
	result = calculator(operation, num1, num2);
	/*printf("%u %c %u = %u\n", num1, operation, num2);*/

	return 0;
}
