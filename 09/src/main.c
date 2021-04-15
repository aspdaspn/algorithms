#include "main.h"
#include "geek.h"

// Adjacency matrix
#define MATRIXSZ 6
#define CHAR_OFFSET_FOR_LETTERS 65

int matrix[MATRIXSZ][MATRIXSZ] = {
			{0, 1, 1, 0, 0, 0},
			{0, 0, 0, 1, 1, 1},
			{0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 0},
};
int visitedDepth[MATRIXSZ] = { 0 };

int getUnvisitedVertex(int ver, int size) {
	for (int i = 0; i < size; ++i) {
		if (matrix[ver][i] == 1 && !visitedDepth[i])
			return i;
	}
	return -1;
}

void depthTraversStack(int st) {
	OneLinkList* stack = (OneLinkList*) malloc(sizeof(OneLinkList));
	initOneLinkList(stack);
	visitedDepth[st] = 1;
	printf("Visited nodes sequence: ");
	printf("%c ", 0 + CHAR_OFFSET_FOR_LETTERS);
	pushOneLinkStack(stack, st);
	
	while (stack -> size != 0) {
		int v = getUnvisitedVertex(stack -> head -> dat, MATRIXSZ);
		if (v == -1) {
			popOneLinkStack(stack);
		} else {
			visitedDepth[v] = 1;
			printf("%c ", v + CHAR_OFFSET_FOR_LETTERS);
			pushOneLinkStack(stack, v);
		}
	}
	printf("\n");

	freeOneLinkStack(stack);
}


void depthTravers(int st) {
	int r;
	printf("%d ", st);

	visitedDepth[st] = 1;
	for (r = 0; r < MATRIXSZ; ++r) {
		if (matrix[st][r] == 1 && !visitedDepth[r]) {
			depthTravers(r);
		}
	}
}

void resetArr() {
	for (int i = 0; i < MATRIXSZ; ++i) {
		visitedDepth[i] = 0;
	}
}


int main(int argc, char** args) {
	// Task 1 Graph DTS with Stack
	depthTraversStack(0);
	resetArr();
	printf("Visited sequence array: ");
	depthTravers(0);
	printf("\n");
	resetArr();

	return EXIT_SUCCESS;
}
