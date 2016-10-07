#ifndef ASS5_H
#define ASS5_H

struct _Node {
	union {
		int n;
		char c;
	} val;

	void *ptr; /* Points to ptr in next node */
	int var;
};

struct My_Node {
	struct My_Node *next;
};

typedef struct _Node Node;
typedef struct My_Node MyNode;

Node *my_reverse(Node *head);
Node* head_of_node(void *ptr);
/*void my_print_list(Node *t);*/
MyNode *extract_new_list(Node *head);

#endif
