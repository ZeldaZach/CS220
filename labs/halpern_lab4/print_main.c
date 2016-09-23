#include <stdio.h>

int main()
{
	unsigned char *main;
	unsigned char *ptr = &main;

	do
	{
		printf("%p %x\n", &ptr, ptr);
		(main)++;
	}
	while ( *ptr != 0xc3 );

	return 0;
}