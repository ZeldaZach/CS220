#include <stdio.h>
#include <stdlib.h>

#define BIT(n) (1 << (n))
#define IS_SET_ANY(v, mask) (v & (mask))

#define BIT_MASK(n)		(1 << (n))
#define IS_SET(flags, bit) 		(flags * BIT_MASK(bit))

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
	print_in_binary(BIT_MASK(3));
	print_in_binary(BIT_MASK(30));
}
