#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define BIT(n) (1 << (n))
#define BIT_SET(v, mask) (v |= (mask))
#define BIT_CLEAR(v, mask) (v &= ~(mask))
#define BIT_FLIP(v, mask) (v ^= (mask))
#define IS_SET_ANY(v, mask) (v & (mask))
#define IS_CLEAR_ANY(b, mask) (v & ~(mask))
#define BIT_MASK(len) (BIT(len) - 1)
#define BF_MASK(start, len) (BIT_MASK(len) << (start))
#define BF_PREP(x, start, len) (((x)&BIT_MASK(len)) << (start))

/* #define BF_GET(y, start, len) ( ((y) >> (start)) & (len) )		/* extract a bitfeld of length "len" starting at bit "start" from y */
#define BF_GET(y, start, len) ( ((y) & (BF_MASK(start, len))) >> (start) )
#define BF_SET(y, x, start, len) (  )

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec
+ 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void timeval_print(char *str, struct timeval *tv)
{
    printf("%s %ld sec, %06ld micro sec\n", str, tv->tv_sec,
tv->tv_usec);
}

void print_in_binary(unsigned int x)
{
	int i;

	for (i = 31; i >= 0; i--)
	{
		if (IS_SET_ANY(BIT(i), x))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

int main()
{
	struct timeval tvDiff, tvStart, tvEnd;
	
	int y = 0x64;
	int start = 0x0;
	int len = 0x7;

	gettimeofday(&tvStart, NULL);

	/*printf("100 = ");
	print_in_binary(100);

	printf("35 = ");
	print_in_binary(35);*/
	
	print_in_binary(y);
	print_in_binary(BF_GET(y, start, len));

	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	timeval_print("\nTIME: ", &tvDiff);
}
