#include <sorter.c>

Node tmp6, tmp7, tmp6_b, tmp7_b;
Node fifth;

void printList(Node *new_head)
{
	printf("**********\n");
	while (new_head)
	{
		printf("0x%x\n", new_head);
		new_head = new_head->next;
	}
	printf("**********\n");
}

int main()
{
	Node *tmp1, *tmp2, *tmp3, tmp4, tmp5, *new_head;
	Node *tmp1_b, *tmp2_b, *tmp3_b, tmp4_b, tmp5_b, *new_head_b;
	Node *first, *second, third, *fourth, *sixth, *new_head_c;

	tmp1 = malloc(sizeof(Node));
	tmp2 = malloc(sizeof(Node));
	tmp3 = malloc(sizeof(Node));
	
	tmp1_b = malloc(sizeof(Node));
	tmp2_b = malloc(sizeof(Node));
	tmp3_b = malloc(sizeof(Node));
	
	first = malloc(sizeof(Node));
	second = malloc(sizeof(Node));
	fourth = malloc(sizeof(Node));
	sixth = malloc(sizeof(Node));
	
	

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
	tmp2->prev = &tmp4;

	tmp3->next = NULL;
	tmp3->prev = &tmp7;

	tmp4.next = tmp2;
	tmp4.prev = &tmp5;

	tmp5.next = &tmp4;
	tmp5.prev = tmp1;

	tmp6.next = &tmp7;
	tmp6.prev = tmp2;
	
	tmp7.next = tmp3;
	tmp7.prev = &tmp6;
	
	/*printf("tmp1 location: 0x%x\n", tmp1);
	printf("tmp5 location: 0x%x\n", &tmp5);
	printf("tmp4 location: 0x%x\n", &tmp4);
	printf("tmp2 location: 0x%x\n", tmp2);	
	printf("tmp6 location: 0x%x\n", &tmp6);
	printf("tmp7 location: 0x%x\n", &tmp7);
	printf("tmp3 location: 0x%x\n\n", tmp3);*/
	
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
	
	new_head = sort_nodes(tmp1);
	printList(new_head);	
	
	
	/*printf("tmp1_b location: 0x%x\n", tmp1_b);
	printf("tmp2_b location: 0x%x\n", tmp2_b);
	printf("tmp3_b location: 0x%x\n", tmp3_b);
	printf("tmp4_b location: 0x%x\n", &tmp4_b);
	printf("tmp5_b location: 0x%x\n", &tmp5_b);
	printf("tmp6_b location: 0x%x\n", &tmp6_b);
	printf("tmp7_b location: 0x%x\n\n", &tmp7_b);*/
	
	new_head_b = sort_nodes(tmp1_b);
	printList(new_head_b);
	
	
	first->next = &third;
	first->prev = 0;
	third.next = fourth;
	third.prev = first;
	fourth->next = second;
	fourth->prev = &third;
	second->next = sixth;
	second->prev = fourth;
	sixth->next = &fifth;
	sixth->prev = second;
	fifth.next = 0;
	fifth.prev = sixth;
	
	new_head_c = sort_nodes(first);
	printList(new_head_c);

	

	return 0;
}
