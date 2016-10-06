#include <stdio.h>
#include <stdlib.h>
#include "main.h"

Node *my_reverse(Node *head)
{
	Node *new_start = malloc(sizeof(Node));
	Node *current, *previous, *next;
	new_start = head;

	while (head->ptr != NULL)
	{
		new_start->ptr = malloc(sizeof(Node));
		head = head_of_node(head->ptr);
		new_start = head;
	}

	/* Now to swap the order of the node list */
	current = new_start->ptr->ptr

	return head;
}

Node *head_of_node(void *ptr)
{
	ptr = &ptr - 0x4;
	
	return ptr;
}

int main()
{
	return 0;
}
