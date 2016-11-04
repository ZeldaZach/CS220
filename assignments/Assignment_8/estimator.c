#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define TOTAL_TIMES 268435455
#define TOTAL_LOOPS 10

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void timeval_print(char *str, struct timeval *tv)
{
    printf("%s %ld sec, %06ld micro sec\n", str, tv->tv_sec, tv->tv_usec);
}

int main()
{
	struct timeval tvDiff, tvStart, tvEnd;
	long long nopANDret = 0, ret = 0;
	int i, j;

	for (j = 0; j < TOTAL_LOOPS; j++)
	{
		/*** Get the NOP + RET times ***/
		gettimeofday(&tvStart, NULL);
		for (i = 0; i < TOTAL_TIMES; i++)
			oneHundredNOP();
		gettimeofday(&tvEnd, NULL);
		timeval_subtract(&tvDiff, &tvEnd, &tvStart);
		/*timeval_print("\nNOP+RET: ", &tvDiff);*/

		nopANDret += tvDiff.tv_sec*1000000 + tvDiff.tv_usec;
		/*printf("NopANDret = %llu\n", nopANDret);*/

		/*** Get the RET time ***/
		gettimeofday(&tvStart, NULL);
		for (i = 0; i < TOTAL_TIMES; i++)
			zeroNOP();
		gettimeofday(&tvEnd, NULL);
		timeval_subtract(&tvDiff, &tvEnd, &tvStart);
		/*timeval_print("RET: ", &tvDiff);*/

		ret += tvDiff.tv_sec*1000000 + tvDiff.tv_usec;
		/*printf("Ret = %llu\n", ret);*/
	}

	nopANDret /= TOTAL_LOOPS;
	ret /= TOTAL_LOOPS;

	printf("Estimate of NOPs per second: %'llu\n", TOTAL_TIMES*100000000LL / (nopANDret - ret) );


}
