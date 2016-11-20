#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>

#define ARRAY_SIZE 2

int g = 10;
jmp_buf buffer; /* Save buffer */

struct var_state
{
	void *address;
	int size;
	unsigned char *data; /* Bytes */
	struct var_state *next;
};

struct var_state *var_state_head = NULL;

void save_state(void *addr, unsigned int size)
{
	int i;
	unsigned char *data;
	struct var_state *new_var_state = malloc(sizeof(struct var_state));

	new_var_state->address = (unsigned int *)(addr);
	new_var_state->size = size;

	/* Copy 'size' bytes into the state saver */
	data = malloc(size);
	memcpy(data, addr, size);
	new_var_state->data = data;

	/* Save state saver to head of linked list */
	new_var_state->next = var_state_head;
	var_state_head = new_var_state;
}

void restore_state()
{
	struct var_state *tmp;

	while (var_state_head)
	{
		/* Copy 'size' bytes from data to saved address */
		memcpy(var_state_head->address, var_state_head->data, var_state_head->size);

		/* Set temp before freeing memory */
		tmp = var_state_head->next;

		/* Free memory saved to avoid memory leak */
		free(var_state_head->data);
		free(var_state_head);

		/* Increment along linked list */
		var_state_head = tmp;
	}
}

void signal_handler(int sig_val)
{
	/*  Signal handler for all potential signals */
	longjmp(buffer, sig_val);
}

void f()
{
	int x, i;
	char *p;
	x = 11;
	p = (char *) malloc(ARRAY_SIZE);
	p[0] = p[1] = 'x';

	/* Register ALL signals for the handler */
	for (i = 0; i < 32; i++)
		signal(i, signal_handler);

	/* Save x, g, and p via save_state on each */
	/* Save memory p points to and p */
	save_state(&x, sizeof(x));
	save_state(&g, sizeof(g));
	save_state(p, ARRAY_SIZE);
	save_state(&p, sizeof(p));

	if (!setjmp(buffer))
	{
		g = 30;
		x = 100;
		p = 0;
		p[0] = p[1] = p[2] = 'x';
	}
	else
	{
		restore_state();
		printf("%d, %d, %c, %c\n", g, x, p[0], p[1]); /* 10, 11, x, x */
	}
}

int main()
{
	f();
}
