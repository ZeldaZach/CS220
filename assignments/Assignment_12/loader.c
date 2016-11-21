#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	unsigned int num1, num2, result, file_size;
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

	/* If binary file does not exist, exit */
	if (!fp)
	{
		printf("File not found\n");
		exit(1);
	}

	/* Get sizeof(input_file) */
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	/* Malloc for raw_bytes & allow us to write into that area */
	raw_bytes = malloc(file_size);
	mprotect(raw_bytes, file_size, PROT_WRITE);

	/* Read file into buffer */
	fread(raw_bytes, file_size, 1, fp);

	/* Make written area readable/executable */
	mprotect(raw_bytes, file_size, PROT_EXEC);
	mprotect(raw_bytes, file_size, PROT_READ);

	/* Cast args appropriately */
	num1 = atoi(argv[2]);
	num2 = atoi(argv[4]);
	operation = *argv[3];

	/* Cast buffer to the calculator() func */
	calculator = (Calc_fptr)raw_bytes;

	/* Activate calculator and print results */
	result = calculator(operation, num1, num2);
	printf("%u %c %u = %u\n", num1, operation, num2, result);

	return 0;
}
