#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

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
	unsigned int address = 0x00003510;
	/* 0000 0011 0101 0001 0000
	   ________________________
	   1111 1111 1198 7654 3210
	   9876 5432 10
	*/
	
	
	unsigned int address2 = 0xFF003FFA;
	/* 1111 1111 0000 0000 0011 1111 1111 1010
	   __________________________________
	   3322 2222 2222 1111 1111 1198 7654 3210
	   1098 7654 3210 9876 5432 10
	*/

#if 0
	printf("NO BITS SET: %x\n", TEST_IF_ANY_SET(address, 0, 3));
	printf("BITS SET: %x\n", TEST_IF_ANY_SET(address, 2, 4));
	printf("BITS SET: %x\n", TEST_IF_ANY_SET(address, 4, 7));
	printf("BITS SET: %x\n", TEST_IF_ANY_SET(address, 4, 8));
	printf("NO BITS SET: %x\n", TEST_IF_ANY_SET(address, 9, 9));
	printf("BITS SET: %x\n", TEST_IF_ANY_SET(address, 11, 13));
	printf("NO BITS SET: %x\n", TEST_IF_ANY_SET(address, 14, 19));

	printf("NOT ALL SET: %x\n", TEST_IF_ALL_SET(address2, 0, 4));
	printf("ALL SET: %x\n", TEST_IF_ALL_SET(address2, 4, 12));
	printf("ALL SET: %x\n", TEST_IF_ALL_SET(address2, 11, 11));
	printf("NOT ALL SET: %x\n", TEST_IF_ALL_SET(address2, 13, 14));
	printf("NOT ALL SET: %x\n", TEST_IF_ALL_SET(address2, 20, 23));
	printf("NOT ALL SET: %x\n", TEST_IF_ALL_SET(address2, 23, 31));
	printf("ALL SET: %x\n", TEST_IF_ALL_SET(address2, 25, 30));
#endif	
	
	

	printf("%-20s", "NOT ALL SET"); print_in_binary( TEST_IF_ALL_SET(address2, 0, 4) );
	printf("%-20s", "NOT ALL SET"); print_in_binary( TEST_IF_ALL_SET(address2, 13, 14) );
	printf("%-20s", "NOT ALL SET"); print_in_binary( TEST_IF_ALL_SET(address2, 20, 23) );
	printf("%-20s", "NOT ALL SET"); print_in_binary( TEST_IF_ALL_SET(address2, 23, 31) );
	
	printf("%-20s", "ALL SET"); print_in_binary( TEST_IF_ALL_SET(address2, 4, 12) );
	printf("%-20s", "ALL SET"); print_in_binary( TEST_IF_ALL_SET(address2, 11, 11) );
	printf("%-20s", "ALL SET"); print_in_binary( TEST_IF_ALL_SET(address2, 25, 30) );
	
	

	return 0;
}
