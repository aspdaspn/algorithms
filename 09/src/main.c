#include "main.h"
#include "geek.h"

// Adjacency matrix
#define MATRIXSZ 6
#define CHAR_OFFSET_FOR_LETTERS 65

int matrix[MATRIXSZ][MATRIXSZ] = {
	//   0  1  2  3  4  5
			{0, 1, 1, 0, 0, 0},	// 0
			{0, 0, 0, 1, 1, 1}, // 1
			{0, 0, 0, 0, 0, 1}, // 2
			{1, 0, 0, 0, 0, 0}, // 3
			{0, 0, 0, 0, 0, 0}, // 4
			{0, 0, 0, 0, 1, 0}, // 5
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

void adjacencyCount(int size, int* adjacencyLinks) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (matrix[j][i] == 1 && i != j)
				adjacencyLinks[i]++;
		}
	}
}

void traversalCount (int start, int size, int* traversalLinks) {
	TwoLinkList* queue = (TwoLinkList*) malloc(sizeof(TwoLinkList));
	initTwoLinkList(queue);
	TwoLinkEnqueue(queue, start);
	while (queue -> size > 0) {
		int idx = TwoLinkDequeue(queue);
		if (visitedDepth[idx] == 1)
			continue;

		visitedDepth[idx] = 1;
		for (int i = 0; i < size; ++i) {
			if (matrix[idx][i] == 1) {
				if (i != idx)
					traversalLinks[i]++;
				if (!visitedDepth[i])
					TwoLinkEnqueue(queue, i);
			}
		}
	}
	freeTwoLinkList(queue);
}

int main(int argc, char** args) {
	// Task 1 Graph DTS with Stack
	depthTraversStack(0);
	resetArr();
	printf("Visited sequence array: ");
	depthTravers(0);
	printf("\n");
	resetArr();

	// Task 2a count adjacent graph nodes for each node, based on matrix
	int adjacencyLinks[MATRIXSZ] = { 0 };
	adjacencyCount(MATRIXSZ, adjacencyLinks);
	printf("Adjacent graph nodes for each node, based on matrix:\n");
	printIntArray(adjacencyLinks, MATRIXSZ, 3);
	
	// Task 2b count adjacent graph nodes with a function
	int traversalLinks[MATRIXSZ] = { 0 };
	resetArr();
	traversalCount(0, MATRIXSZ, traversalLinks);
	printf("Adjacent graph nodes for each node, by graph traversal: \n");
	printIntArray(traversalLinks, MATRIXSZ, 3);

	return EXIT_SUCCESS;
}
