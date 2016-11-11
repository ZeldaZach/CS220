#include <stdio.h>
#include <stdlib.h>
#include "macros.h"

int main()
{	
	unsigned int address = 0x00003510; /* 0000 0011 0101 0001 0000 */
	unsigned int address2 = 0xFF003FFA; /* 1111 1111 0000 0000 0011 1111 1111 1010 */

	printf("BITS SET (true): %s\n", TEST_IF_ANY_SET(address, 2, 4) ? "true" : "false");
	printf("BITS SET (true): %s\n", TEST_IF_ANY_SET(address, 4, 7) ? "true" : "false");
	printf("BITS SET (true): %s\n", TEST_IF_ANY_SET(address, 4, 8) ? "true" : "false");
	printf("BITS SET (true): %s\n", TEST_IF_ANY_SET(address, 11, 13) ? "true" : "false");
	printf("BITS SET (true): %s\n", TEST_IF_ANY_SET(address, 0, 31) ? "true" : "false");
	printf("BITS SET (false): %s\n", TEST_IF_ANY_SET(address, 0, 3)  ? "true" : "false");
	printf("BITS SET (false): %s\n", TEST_IF_ANY_SET(address, 9, 9) ? "true" : "false");
	printf("BITS SET (false): %s\n", TEST_IF_ANY_SET(address, 14, 19) ? "true" : "false");
	printf("\n");
	printf("ALL SET (false): %s\n", TEST_IF_ALL_SET(address2, 0, 4)  ? "true" : "false");
	printf("ALL SET (false): %s\n", TEST_IF_ALL_SET(address2, 13, 14) ? "true" : "false");
	printf("ALL SET (false): %s\n", TEST_IF_ALL_SET(address2, 20, 23) ? "true" : "false");
	printf("ALL SET (false): %s\n", TEST_IF_ALL_SET(address2, 23, 31) ? "true" : "false");
	printf("ALL SET (false): %s\n", TEST_IF_ALL_SET(address2, 23, 31) ? "true" : "false");
	printf("ALL SET (false): %s\n", TEST_IF_ALL_SET(address2, 0, 31) ? "true" : "false");
	printf("ALL SET (true): %s\n", TEST_IF_ALL_SET(address2, 4, 12)  ? "true" : "false");
	printf("ALL SET (true): %s\n", TEST_IF_ALL_SET(address2, 11, 11) ? "true" : "false");
	printf("ALL SET (true): %s\n", TEST_IF_ALL_SET(address2, 25, 30)  ? "true" : "false");
	printf("\n");
	printf("TOTAL BITS SET (0): %d\n", COUNT_NUM_SET(address, 0, 3));
	printf("TOTAL BITS SET (0): %d\n", COUNT_NUM_SET(address2, 14, 23));
	printf("TOTAL BITS SET (1): %d\n", COUNT_NUM_SET(address, 0, 7));
	printf("TOTAL BITS SET (2): %d\n", COUNT_NUM_SET(address, 0, 8));
	printf("TOTAL BITS SET (4): %d\n", COUNT_NUM_SET(address, 8, 15));
	printf("TOTAL BITS SET (5): %d\n", COUNT_NUM_SET(address, 0, 31));
	printf("TOTAL BITS SET (5): %d\n", COUNT_NUM_SET(address2, 0, 6));
	printf("TOTAL BITS SET (8): %d\n", COUNT_NUM_SET(address2, 4, 11));
	printf("TOTAL BITS SET (20): %d\n", COUNT_NUM_SET(address2, 0, 31));

	return 0;
}
