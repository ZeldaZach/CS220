#include <stdio.h>

int main()
{
	int a = 0xe;
	int *b = &a;
	int **c = &b;
	int ***d = &c;

	printf("a.Address= %p a.Value= %x\n", &a, a);
	printf("b.Address= %p b.Value= %x\n", &b, b);
	printf("c.Address= %p c.Value= %x\n", &c, c);
	printf("d.Address= %p d.Value= %x\n", &d, d);
}