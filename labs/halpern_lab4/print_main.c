#include <stdio.h>

int main()
{
	unsigned char *ptr = (unsigned char *) &main;

	*ptr = 0;

	do
	{
		printf("%x \n", *ptr);
		(ptr)++;
	}
	while ( *ptr != 0xc3 );

	return 0;
}