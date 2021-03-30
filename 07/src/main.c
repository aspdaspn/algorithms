#include "main.h"

#define T char

typedef struct Node {
	T dat;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	int size;
} Stack;

void init(Stack *stack) {
	stack -> head = NULL;
	stack -> size = 0;
}

bool push(Stack *stack, T value) {
	Node *tmp = (Node *) malloc(sizeof(Node));
	if (tmp == NULL) {
		printf("Stack overflow\n");
		return false;
	}
	tmp -> dat = value;
	tmp -> next = stack -> head;

	stack -> head = tmp;
	stack -> size ++;
	return true;
}

T pop(Stack *stack) {
	if (stack -> size == 0) {
		printf("Stack is empty\n");
		return -1;
	}

	Node *tmp = stack -> head;
	T data = stack -> head -> dat;
	stack -> head = stack -> head -> next;
	stack -> size --;
	free(tmp);
	return data;
}

void printNode(Node *n) {
	if (n == NULL) {
		printf("[]");
		return;
	}
	printf("[%c] ", n -> dat);
}

void printStack(Stack *stack) {
	Node *current = stack -> head;
	if (current == NULL)
		printNode(current);
	else
		do {
			printNode(current);
			current = current -> next;
		} while (current != NULL);

	printf(" Size: %d\n", stack -> size);
}

int main(int argc, char** args) {
	Stack *st = (Stack *)malloc(sizeof(Stack));
	init(st);
	push(st, 'a');
	push(st, 'b');
	push(st, 'c');
	push(st, 'd');
	push(st, 'e');
	printStack(st);
	printf("%c\n", pop(st));
	printStack(st);
	printf("%c\n", pop(st));
	printStack(st);
	printf("%c\n", pop(st));
	printStack(st);
	printf("%c\n", pop(st));
	printf("%c\n", pop(st));
	printf("%c\n", pop(st));
	return EXIT_SUCCESS;
}
