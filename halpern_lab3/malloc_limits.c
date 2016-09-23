#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0;
    int *dfoo = (int *) malloc(0x1000);
	int *cfoo = (int *) malloc(0x1000);
	int *efoo = (int *) malloc(0x1000);
    int *ffoo = (int *) malloc(0x1000);
	int *gfoo = (int *) malloc(0x1000);
	int *hfoo = (int *) malloc(0x1000);
	
    for (i = 0; i < 1000000; i++)
    {
        dfoo = (int *) malloc(i * 0xFFFF * 0xFFFF);
		cfoo = (int *) malloc(i * 0xFFFF* 0xFFFF);
		efoo = (int *) malloc(i * 0xFFFF* 0xFFFF);
        ffoo = (int *) malloc(i * 0xFFFF* 0xFFFF);
		gfoo = (int *) malloc(i * 0xFFFF* 0xFFFF);
		hfoo = (int *) malloc(i * 0xFFFF* 0xFFFF);
    }
    return 0;
}

