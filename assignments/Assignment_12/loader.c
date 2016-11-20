#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	typedef int (*Calc_fptr)(char, int, int);
	unsigned int num1, num2;
	long f_size;
	char raw_bytes[99], operation;
	Calc_fptr calc;

	if (argc != 5)
	{
		printf("Usage %s <filename><uint><operation><uint>\n", argv[0]);
		exit(1);
	}

	fp = fopen(argv[0], "rb"); /* Open/read binary file */

	/* Read file into buffer */
	fread(raw_bytes, sizeof(raw_bytes), 1, fp);

	/* Cast args appropriately */
	num1 = atoi(argv[2]);
	num2 = atoi(argv[4]);
	operation = *argv[3];

	/* Cast buffer to the calc() func */
	calc = (Calc_fptr) raw_bytes;

	/* Print results */
	printf("%u %c %u = %u\n", num1, operation, num2, calc(operation, num1, num2));

	return 0;
}
