#include <stdio.h>
#include <stdlib.h>

extern unsigned int *getBasePointer();
extern int main();

/*void foo1();
void foo2();
void foo3();
void print_backtrace(int count);
*/


/*void foo1()
{
	int a = 1;
	char d = 'd';
	char* w = "Hello\0";

	foo2();
}

void foo2()
{
	int a = 2;
	float e = 3.14;
	long x = 305805;
	foo3();
}

void foo3()
{
	int a = 3;
	char e = 'e';
	char f = 'f';
	print_backtrace(4);
}*/

void print_backtrace(int count)
{
	unsigned int *curr_ebp, ret_addr;
	unsigned char *ptr = (unsigned char *)(&main);
	do { (ptr)++; } while (*ptr != 0xC3);

	curr_ebp = getBasePointer();

	while (count > 0)
	{
		ret_addr = (unsigned int) *(curr_ebp + 0x1);
		printf("Ret: %x\n", ret_addr);

		if ((unsigned int)(main) < ret_addr && ret_addr < (unsigned int)(ptr))
		{
			printf("MAIN\n");
			return;
		}

		curr_ebp = (unsigned int *)*(curr_ebp);
		count--;
	}
}

/*int main()
{
	printf("%-20s %x\n", "Address of Main", &main);
	printf("%-20s %x\n", "Address of Foo1", &foo1);
	printf("%-20s %x\n", "Address of Foo2", &foo2);
	printf("%-20s %x\n", "Address of Foo3", &foo3);
	foo1();
}*/
