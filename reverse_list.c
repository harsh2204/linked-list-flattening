//HOW TO REVERSE A LIST
//
// INPUT	: L -> | 7 | -> | 1 | -> | 5 | -> | 3 | -> NULL
//
// OUTPUT	: L -> | 3 | -> | 5 | -> | 1 | -> | 7 | -> NULL
//
// Pseudo Code
//
// reverse(L)
// 	if (L == NULL)	return NULL;
// 	p = reverse(L->next);
//	attach node at L to p
//	p -> | 3 | -> | 5 | -> | 1 | -> | 7 |
//
//Definition of reverse for a sequence of numbers L
//
// L = <1, 2, 3, 4>
// L = (head(L), tail(L)) = (head = <1>, tail = <2, 3, 4>)
// reverse(L) = (reverse(tail(L)), head(L)) = (reverse(<2, 3, 4>), <1>) = 4, 3, 2, <1>
//
//CODE!
struct node *reverse(struct node *L)
{
	// !L == (L == NULL)
	if(!L)
		return NULL;
	struct node *head = L;
	struct node *tail = head->next;
	if(!tail)
		return head;
	struct node *rev = reverse(tail);
	struct node *last = rev;
	//Grab the last node of the reversed list
	while(last->next)
		last = last->next;
	//Attach the original head to it
	last->next = head;
	head->next = NULL;
	return rev;
}

printReverse(L)
{
	if(!L)
		return;
	head(L), tail(L);
	printReverse(tail(L));
	print(head(L));
}

void print(L, char *s1)
{
	printf("%d", L->key);
	printf("%s", s1);
}

printFlattened(L)
{
	print(L, "\n");
	
}