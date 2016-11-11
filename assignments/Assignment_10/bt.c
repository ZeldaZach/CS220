#include <stdio.h>
#include <stdlib.h>

extern unsigned int *getBasePointer();
extern int main();

/*
void foo1();
void foo2();
void foo3();
void print_backtrace(int count);


void foo1()
{
	foo2();
}

void foo2()
{
	foo3();
}

void foo3()
{
	print_backtrace(4);
}
*/

void print_backtrace(int count)
{
	unsigned int *curr_ebp, ret_addr;
	unsigned char *ptr = (unsigned char *)(&main);
	do { (ptr)++; } while (*ptr != 0xC3);

	curr_ebp = getBasePointer();

	while (count > 0)
	{
		ret_addr = (unsigned int) *(curr_ebp + 0x1);
		printf("%x\n", ret_addr);

		/* Start address of main < current addr on stack < end address of main */
		if ((unsigned int)&main < ret_addr && ret_addr < (unsigned int)&ptr)
			return;

		curr_ebp = (unsigned int *)*(curr_ebp);
		count--;
	}
}

/*
int main()
{
	printf("%-20s %x\n", "Address of Main", &main);
	printf("%-20s %x\n", "Address of Foo1", &foo1);
	printf("%-20s %x\n", "Address of Foo2", &foo2);
	printf("%-20s %x\n", "Address of Foo3", &foo3);
	foo1();
}
*/