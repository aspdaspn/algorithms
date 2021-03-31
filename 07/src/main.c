#include "main.h"

#define T char
#define STRINGSIZE 81

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

T check(Stack *stack) {
	if (stack -> size == 0) {
		printf("Stack is empty\n");
		return -1;
	}
	return stack -> head -> dat;
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

void copyList(Stack *from, Stack *to) {
	if (from -> size == 0) {
		printf("Empty Source, nothing to copy.\n");
		return;
	}
	Node *current = from -> head;
	do {
	Node *tmp = (Node *) malloc(sizeof(Node));
	if (tmp == NULL) {
		printf("Stack overflow\n");
		return;
	}
	tmp -> dat = current -> dat;
	tmp -> next = to -> head;
	to -> head = tmp;
	current = current -> next;
	} while (current != NULL);
}

bool ifSorted(Stack *stack) {
	Node *current = stack -> head;
	if (current == NULL) {
		printf("Empty stack\n");
		return false;
	}
	Node comp;
	comp.dat = current -> dat;
	while (current != NULL) {
		if (comp.dat > current -> dat)
			return false;
		comp.dat = current -> dat;
		current = current -> next;
	}
	return true;
}

void checkBraces(Stack *stack) {
	char ts[STRINGSIZE];
	int i = 0;

	printf("Enter test string: ");
	fgets(ts, sizeof(ts) / sizeof(char), stdin);
	while (ts[i] != '\0') {
			if (ts[i] == '(' || ts[i] == '[' || ts[i] == '{' )
				push(stack, ts[i]);
			if (ts[i] == ')' || ts[i] == ']' || ts[i] == '}' )
				switch(check(stack)) {
					case '(':
						if (ts[i] == ')')
							pop(stack);
						break;
					case '[':
						if (ts[i] == ']')
							pop(stack);
						break;
					case '{':
						if (ts[i] == '}')
							pop(stack);
						break;
				}
			i++;
	}
	printf("%s\n", (stack -> size == 0) ? "Braces are correct" : "Braces are wrong");
}

int main(int argc, char** args) {
	// Task 1, Check Braces
	Stack *br = (Stack *) malloc(sizeof(Stack));
	init(br);
	checkBraces(br);
	// Task 2 Copy Dymamic List
	Stack *st = (Stack *) malloc(sizeof(Stack));
	init(st);
	push(st, 'a');
	push(st, 'b');
	push(st, 'c');
	push(st, 'd');
	push(st, 'e');
	printStack(st);
	Stack *cp = (Stack *) malloc(sizeof(Stack));
	init(cp);
	copyList(st, cp);
	printStack(cp);
	// Task 3, if List is sorted
	printf("%s\n", ifSorted(cp) ? "List is sorted" : "List is not sorted");
	return EXIT_SUCCESS;
}
