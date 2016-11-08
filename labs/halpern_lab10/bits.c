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
#define BF_GET(y, start, len) ( ((y) >> (start)) & BIT_MASK(len) )
#define BF_SET(y, x, start, len) ( ((y) &~ BF_MASK(start, len)) | BF_PREP(x, start, len) )

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

/* (0xf712c0d0)
1 1 1 1 0 1 1 1 0 0 0 1 0 0 1 0 1 1 0 0 0 0 0 0 1 1 0 1 0 0 0 0
_______________________________________________________________
3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1 9 8 7 6 5 4 3 2 1 0
1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
*/

unsigned int get_page_offset(unsigned int address)
{
	/* Bits 0 -> 11 */
	return BF_GET(address, 0, 12);
}

unsigned int get_tlb_id(unsigned int address)
{
	/* Bits 12 -> 14 */
	return BF_GET(address, 12, 3);
}

unsigned int get_tlb_tag(unsigned int address)
{
	/* Bits 24 -> 31 */
	return BF_GET(address, 24, 8);
}

unsigned int set_page_offset(unsigned int address, unsigned int new_offset)
{
	return BF_SET(address, new_offset, 0, 12);
}

unsigned int set_tlb_id(unsigned int address, unsigned int new_tlb_id)
{
	return BF_SET(address, new_tlb_id, 12, 3);
}

unsigned int set_tlb_tag(unsigned int address, unsigned int new_tag)
{
	return BF_SET(address, new_tag, 24, 8);
}

int main()
{
	struct timeval tvDiff, tvStart, tvEnd;
	unsigned int address = 0xf712c0d0, page_offset = 0x1a3, tlb_id = 0x0, tlb_tag = 0x84, new_address = address;
	gettimeofday(&tvStart, NULL);

	printf("%-20s", "Address:"); print_in_binary(address);

	/* Test get functions */
	printf("%-20s", "Page offset:"); print_in_binary(get_page_offset(address));
	printf("%-20s", "TLB id:"); print_in_binary(get_tlb_id(address));
	printf("%-20s", "TLB tag:"); print_in_binary(get_tlb_tag(address));

	/* Test set functions */
	printf("\n%-20s", "Start Address:"); print_in_binary(new_address);

	new_address = set_page_offset(new_address, page_offset);
	printf("%-20s", "New page offset:"); print_in_binary(get_page_offset(new_address));

	new_address = set_tlb_id(new_address, tlb_id);
	printf("%-20s", "New TLB id:"); print_in_binary(get_tlb_id(new_address));

	new_address = set_tlb_tag(new_address, tlb_tag);
	printf("%-20s", "New TLB tag:"); print_in_binary(get_tlb_tag(new_address));

	printf("%-20s", "End Address:");print_in_binary(new_address);

	gettimeofday(&tvEnd, NULL);
	timeval_subtract(&tvDiff, &tvEnd, &tvStart);
	timeval_print("\nTIME: ", &tvDiff);
}
