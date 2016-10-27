#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Node tmp6, tmp7, tmp6_b, tmp7_b;

void swap(Node *a, Node *b)
{
	Node *tmp1 = malloc(sizeof(Node));

	if (a == b)
		return;

	if (a->next == b)
	{
		a->next = b->next;
		b->prev = a->prev;
		
		if (a->next)
		{
			a->next->prev = a;
		}
		
		if (b->prev)
		{
			b->prev->next = b;
		}
		
		b->next = a;
		a->prev = b;
	}
	else
	{
		tmp1->prev = b->prev;
		tmp1->next = b->next;

		b->prev = a->prev;
		b->next = a->next;

		a->prev = tmp1->prev;
		a->next = tmp1->next;
		
		if (b->next)
		{
			b->next->prev = b;
		}
		
		if (b->prev)
		{
			b->prev->next = b;
		}
		
		if (a->next)
		{
			a->next->prev = a;
		}
		
		if (a->prev)
		{
			a->prev->next = a;
		}
		
		if (a->next == NULL)
		{
			printf("start->next is NULL w/ start = (0x%x)\n", a);
		}
		if (b->next == NULL)
		{
			printf("largest->next is NULL w/ largest = (0x%x)\n", b);
		}
	}
}

void printList(Node *new_head)
{
	printf("*****PRINTING LIST*****\n");
	while (new_head)
	{
		printf("VAL 0x%x\n", new_head);
		new_head = new_head->next;
	}
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
	if (start->next)
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
		
		/* printf("LARGEST: 0x%x\n", largest); */
		real_head = largest;
	}
	swap(start, largest);
	/*printList(real_head);*/
	
	/* Start a while */
	
	/*
	NULL -> 1 -> 5 -> 4 -> 2 -> 6 -> 7 -> 3 -> NULL
	
	NULL -> 1 -> 5
	3 -> 1 -> 5
	
	*/
	tmp_rl = real_head;
	while (1)
	{
		tmp_rl = real_head;
		for (i = 0; i < timesToNext; i++)
		{
			tmp_rl = tmp_rl->next;
		}
		timesToNext++;
	
		start = tmp_rl;
		if (start->next)
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
		
			/* printf("LARGEST: 0x%x\n", largest); */
		}
		else
		{
			break; /* No next element! */
		}
		
		swap(start, largest);
		
		/*printList(real_head);*/
	}

	return real_head;
}

int main()
{
	Node *tmp1, *tmp2, *tmp3, tmp4, tmp5, *new_head;
	Node *tmp1_b, *tmp2_b, *tmp3_b, tmp4_b, tmp5_b, *new_head_b;

	tmp1 = malloc(sizeof(Node));
	tmp2 = malloc(sizeof(Node));
	tmp3 = malloc(sizeof(Node));
	
	tmp1_b = malloc(sizeof(Node));
	tmp2_b = malloc(sizeof(Node));
	tmp3_b = malloc(sizeof(Node));
	

	/***************	
		1 -> 5
		2 -> 6
		3 -> NULL
		4 -> 2
		5 -> 4
		6 -> 7
		7 -> 3
		NULL -> 1 -> 5 -> 4 -> 2 -> 6 -> 7 -> 3 -> NULL
	***************/
	tmp1->next = &tmp5;
	tmp1->prev = NULL;

	tmp2->next = &tmp6;
	tmp2->prev = tmp2;

	tmp3->next = NULL;
	tmp3->prev = &tmp6;

	tmp4.next = tmp2;
	tmp4.prev = &tmp5;

	tmp5.next = &tmp4;
	tmp5.prev = tmp1;

	tmp6.next = &tmp7;
	tmp6.prev = tmp2;
	
	tmp7.next = tmp3;
	tmp7.prev = &tmp6;
	
	printf("tmp1 location: 0x%x\n", tmp1);
	printf("tmp5 location: 0x%x\n", &tmp5);
	printf("tmp4 location: 0x%x\n", &tmp4);
	printf("tmp2 location: 0x%x\n", tmp2);	
	printf("tmp6 location: 0x%x\n", &tmp6);
	printf("tmp7 location: 0x%x\n", &tmp7);
	printf("tmp3 location: 0x%x\n\n", tmp3);
	
	tmp1_b->next = tmp2_b;
	tmp1_b->prev = NULL;

	tmp2_b->next = tmp3_b;
	tmp2_b->prev = tmp1_b;

	tmp3_b->next = &tmp5_b;
	tmp3_b->prev = tmp2_b;

	tmp4_b.next = &tmp7_b;
	tmp4_b.prev = &tmp6_b;

	tmp5_b.next = &tmp6_b;
	tmp5_b.prev = tmp3_b;

	tmp6_b.next = &tmp4_b;
	tmp6_b.prev = &tmp5_b;
	
	tmp7_b.next = NULL;
	tmp7_b.prev = &tmp4_b;
	
	printf("tmp1_b location: 0x%x\n", tmp1_b);
	printf("tmp2_b location: 0x%x\n", tmp2_b);
	printf("tmp3_b location: 0x%x\n", tmp3_b);
	printf("tmp4_b location: 0x%x\n", &tmp4_b);
	printf("tmp5_b location: 0x%x\n", &tmp5_b);
	printf("tmp6_b location: 0x%x\n", &tmp6_b);
	printf("tmp7_b location: 0x%x\n\n", &tmp7_b);
	
	new_head_b = sort_nodes(tmp1_b);
	printf("RESULT FROM new_head\n");
	printList(new_head_b);
		
	new_head = sort_nodes(tmp1);
	printf("RESULT FROM new_head\n");
	printList(new_head);

	return 0;
}
