#include <stdio.h>
#include <time.h>

void forLoop(unsigned int n) {
	unsigned int i;
	for(i = 0; i < n; i++)
		;
}

void whileLoop(unsigned int n) {
	while(n > 0)
		n--;
}

void doWhileLoop(unsigned int n) {
	do { n--; } while (n > 0);
}

int main()
{
	/* For Loop */
    clock_t tic = clock();
	forLoop(1000000000);
    clock_t toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
	
	/* While Loop */
    tic = clock();
	whileLoop(1000000000);
    toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);
	
	/* Do While Loop */
    tic = clock();
	doWhileLoop(1000000000);
    toc = clock();
    printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    return 0;
}
