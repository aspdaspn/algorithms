#include "main.h"

// Adjacency matrix
#define MATRIXSZ 6
int matrix[MATRIXSZ][MATRIXSZ] = {
			{0, 1, 1, 0, 0, 0},
			{0, 0, 0, 1, 1, 1},
			{0, 0, 0, 0, 0, 1},
			{1, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 0},
};
int visitedDepth[MATRIXSZ] = { 0 };

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
	depthTravers(0);
	resetArr();
	printf("\n");
	depthTravers(2);
	resetArr();
	printf("\n");
	depthTravers(1);
	resetArr();
	printf("\n");
	return EXIT_SUCCESS;
}
