#ifndef MAIN_H
#define MAIN_H

struct _Node {
	union {
		int n;
		char c;
	} val;

	void *ptr; /* Points to ptr in next node */
	int var;
};

typedef struct _Node Node;

#endif
