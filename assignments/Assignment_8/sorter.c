#include <stdio.h>
#include <stdlib.h>
#include "node.h"

/* Taken from https://ptspts.blogspot.com/2010/01/how-to-swap-two-nodes-in-doubly-linked.html */
void swap(Node *node1, Node *node2)
{
	Node *temp;
	temp = node1->next;
	node1->next = node2->next;
	node2->next = temp;

	if (node1->next != NULL)
		node1->next->prev = node1;

	if (node2->next != NULL)
		node2->next->prev = node2;

	temp = node1->prev;
	node1->prev = node2->prev;
	node2->prev = temp;

	if (node1->prev != NULL)
		node1->prev->next = node1;

	if (node2->prev != NULL)
		node2->prev->next = node2;
}

Node *sort_nodes(Node *head)
{
	Node *start = head;
	Node *largest;
	Node *trav;
	Node *real_head; /* DO NOT EDIT */
	Node *tmp_rl;
	int i;
	int timesToNext = 1;
	
	/* SET REAL HEAD */
	if (start)
	{
		largest = start; /* Addr of Start */
		trav = start->next;
		while(trav)
		{
			if (largest < trav) /* Addr of largest < Addr of start */
			{
				largest = trav;
			}
			trav = trav->next;
		}
		
		real_head = largest;
	}
	swap(start, largest);

	while (1)
	{
		tmp_rl = real_head;
		for (i = 0; i < timesToNext; i++)
			tmp_rl = tmp_rl->next;
		timesToNext++;

		if (tmp_rl)
		{
			largest = tmp_rl; /* Addr of Start */
			trav = tmp_rl->next;
			while(trav)
			{
				if (largest < trav) /* Addr of largest < Addr of start */
				{
					largest = trav;
				}
				trav = trav->next;
			}
		}
		else
		{
			break; /* No next element! */
		}
		
		swap(tmp_rl, largest);
	}

	return real_head;
}
