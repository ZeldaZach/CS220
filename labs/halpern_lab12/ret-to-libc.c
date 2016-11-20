#include <stdio.h>
#include <stdlib.h>

extern unsigned long *get_ebp();

void ret2libc(int dummy)
{
	char *command = "/bin/zsh";
	long *curr_ebp = get_ebp();

	curr_ebp[2] = curr_ebp[1]; /* Save old ret val */
	curr_ebp[1] = (unsigned long)&system; /* Change ret val to &system */
	curr_ebp[3] = (unsigned long)command; /* Set a command for system :) */
}

void ret2libc_generic(char *cmd)
{
	long *curr_ebp = get_ebp();

	curr_ebp[3] = curr_ebp[2]; /* Set system arg to *cmd */
	curr_ebp[2] = curr_ebp[1]; /* Set ret from system as real ret */
	curr_ebp[1] = (unsigned long)&system; /* Set ret val to system */

}

int main()
{
	ret2libc(0);
	ret2libc_generic("ls -lah");
	printf("Done!\n");
	return 0;
}
