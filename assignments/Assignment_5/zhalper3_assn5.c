#include <stdio.h>
#include <stdlib.h>
#include "zhalper3_assn5.h"

MyNode *extract_new_list(Node *head)
{
	return (MyNode *)&(head->ptr);
}

void my_print_list(Node *t)
{
	while (t)
	{
		printf("%d\n", t->val.n);
		t = head_of_node(t->ptr);
	}
}

Node* head_of_node(void *ptr)
{
	Node tmp;
	int offset = (unsigned char *)&(tmp.ptr) - (unsigned char *)&tmp;
	
	if (!ptr)
		return NULL;
	
	return (Node *)((unsigned char *)ptr - offset);
}


Node *my_reverse(Node *head)
{
	MyNode *new_head = extract_new_list(head); /* Move the Node head to a MyNode head */	
	MyNode *currentNode, *previousNode, *nextNode;
	
	/* Reversal of linkedlist taken from http://algorithms.tutorialhorizon.com/reverse-a-linked-list/ */
	currentNode = new_head;
	nextNode = NULL;
	previousNode = NULL;
	
	while (currentNode)
	{
		nextNode = currentNode->next;
		currentNode->next = previousNode;
		previousNode = currentNode;
		currentNode = nextNode;
	}

	my_print_list(head_of_node(previousNode));	
	return head_of_node(previousNode);
}

