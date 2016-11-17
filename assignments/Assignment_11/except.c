#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

#define ARRAY_SIZE 3

int g = 10; /* Global var */
jmp_buf buffer;

struct var_state
{
	unsigned int *address;
	int size;
	unsigned char *data;
	struct var_state *next;
};

struct var_state *var_state_head;

void save_state(void *addr, unsigned int size)
{
	int i;
	unsigned char *data;
	struct var_state *new_var_state = malloc(sizeof(struct var_state));

	new_var_state->address = (unsigned int *)(&addr);
	new_var_state->size = size;
	new_var_state->next = var_state_head;

	data = malloc(size);
	printf("Saving address %p\n", new_var_state->address);
	printf("Saving data:\n");
	/*new_var_state->data =;*/

	for (i = 0; i < size; i++)
	{
		data[i] = *((unsigned char *)&addr + i);
		printf("Byte %x\n", (unsigned)data[i]);
	}
	printf("\n");
	new_var_state->data = data;
	var_state_head = new_var_state;
}

void restore_state()
{
	int i;

	while (var_state_head)
	{
		for (i = 0; i < var_state_head->size; i++)
		{
			*((unsigned char *)var_state_head->address + i) = var_state_head->data[i];
			printf("Restored: %x at address %p\n", var_state_head->data[i], (unsigned char *)var_state_head->address + i);
		}
		printf("\n");

		var_state_head = var_state_head->next;
	}
}

/*  Signal handler */
void signal_handler(int sig_val)
{
	switch (sig_val)
	{
		case SIGSEGV:
		case SIGINT:
		case SIGALRM:
		longjmp(buffer, sig_val);
		break;

		default: break;
	}
}

void f()
{
	int x;
	char *p;
	x = 11;
	p = (char *) malloc(ARRAY_SIZE);
	p[0] = p[1] = 'x';

	signal(SIGSEGV, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGALRM, signal_handler);

	/* Save x, g, and p via save_state on each */
	/* Save memory p points to and p */
	save_state(&x, 4);
	save_state(&g, 4);
	save_state(&p, ARRAY_SIZE);

	if (setjmp(buffer) == 0)
	{
		g = 30;
		x = 100;
		p = 0;
		p[0] = p[1] = p[2] = 'x';
	}
	else
	{
		restore_state();
		printf("Make restore work\n");
		printf("%d, %d, %c, %c\n", g, x, p[0], p[1]); /* 10, 11, x, x */
	}
}

int main()
{
	f();
}
