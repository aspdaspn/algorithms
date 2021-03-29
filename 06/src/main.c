#include "main.h"

#define SZ 10				// Size for Queue
#define SIZE 100		// Size for Stack
#define T int

typedef struct {
	int pr;		//Item priority
	int dat;	// Data
} Node;

Node *arr[SZ];
int head;
int tail;
int items;

// Init array with 0
void init() {
	for (int i = 0; i < SZ; ++i) {
		arr[i] = NULL;
	}
	head = 0;
	tail = 0;
	items = 0;
}

void ins(int pr, int dat) {
	if (items <= SZ) {
		Node *node = (Node *) malloc (sizeof(Node));
		node -> dat = dat;
		node -> pr = pr;
		arr[tail++] = node;
		items++;
	} else
		printf("Queue is full\n");
}

Node *rem() {
	if (items == 0)
		return NULL;
	else {
		int idx = head;
		Node *tmp = arr[head];
		int flag = 0;
		idx++;
		
		while (idx < items) {
			if (tmp -> pr > arr[idx] -> pr) {
				tmp = arr[idx];
				flag = idx;
			}
			idx++;
		}
		idx = flag;
		
		while (flag < items) {
			arr[flag] = arr[idx + 1];
			++flag;
			++idx;
		}

		--tail;
		arr[tail] = NULL;
		--items;
		
		return tmp;
	}
}

void printQueue() {
	printf("[ ]");
	for (int i = 0; i < SZ; ++i) {
		if (arr[i] == NULL)
			printf("[*, *] ");
		else
			printf("[%d, %d] ", arr[i] -> pr, arr[i] -> dat);
	}
	printf(" ]\n");
}


int cursor = -1;
T Stack[SIZE];

bool push(T data)
{
	if (cursor < SIZE)
	{
		Stack[++cursor] = data;
		return true;
	}
	else
	{
		printf("Stack overflow\n");
		return false;
	}
}

T pop()
{
	if (cursor != -1)
		return Stack[cursor--];
	else
	{
		printf("Stack is empty\n");
		return -1;
	}
}

int dec2bin(int dec) {
	while (dec > 0) {
		push(dec % 2);
		dec = dec / 2;
	}
}

int main(int argc, char** args) {
	// Task 1
	{
		init();
		ins(1, 11);
		ins(3, 22);
		ins(4, 33);
		ins(2, 44);
		ins(3, 55);
		ins(4, 66);
		ins(5, 77);
		ins(1, 88);
		ins(2, 99);
		ins(6, 100);

		printQueue();

		for (int i = 0; i < 7; ++i)
		{
			Node *n = rem();
			printf("pr = %d, dat = %d\n", n->pr, n->dat);
		}

		printQueue();

		ins(1, 110);
		ins(3, 120);
		ins(6, 130);

		printQueue();

		for (int i = 0; i < 5; ++i)
		{
			Node *n = rem();
			printf("pr = %d, dat = %d\n", n->pr, n->dat);
		}

		printQueue();
	}
	// Task 2
	{
		int decnum = 8;
		dec2bin(decnum);
		while (cursor != -1)
			printf("%d", pop());
	printf("\n");
	}

	return EXIT_SUCCESS;
}
