#include <stdlib.h>

struct Node {
	int x;
	int y;
	struct Node *next;
};

static struct Node *root; 

void push(int y, int x)
{
	struct Node *p, *q;
	
	p = (struct Node *)malloc(sizeof(struct Node));
	
	if (!p) {
		return;
	}

	p->x = x;
	p->y = y;
	p->next = root;	
	root = p;
}

int pop(int *y, int *x)
{
	struct Node *p;

	if (!root) {
		return 0;
	}

	*y = root->y;
	*x = root->x;

	p = root;
	root = root->next;
	free(p);

	return 1;
}
