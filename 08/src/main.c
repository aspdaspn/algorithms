#include "main.h"

typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
} BinTreeIntNode;

FILE *file;

BinTreeIntNode* treeInsert(BinTreeIntNode *t, int data) {
	BinTreeIntNode *newNode;
	newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
	newNode -> key = data;
	newNode -> left = NULL;
	newNode -> right = NULL;
	BinTreeIntNode *current = t;
	BinTreeIntNode *parent = t;
	if (t == NULL) {
		t = newNode;
	} else {
		while (current -> key != data) {
			parent = current;
			if (current -> key > data) {
				current = current -> left;
				if (current == NULL) {
					parent -> left = newNode;
					return t;
				}
			} else {
				current = current -> right;
				if (current == NULL) {
					parent -> right = newNode;
					return t;
				}
			}
		}
	}
	return t;
}

void printBinTree(BinTreeIntNode *root) {
	if (root) {
		printf("%d", root -> key);
		if (root -> left || root -> right) {
			printf("(");
			if (root -> left)
				printBinTree(root -> left);
			else
				printf("NULL");
			printf(",");
			if (root -> right)
				printBinTree(root -> right);
			else
				printf("NULL");
			printf(")");
		}
	}
}

BinTreeIntNode* getSuccessor(BinTreeIntNode *node) {
	BinTreeIntNode *current = node -> right;
	BinTreeIntNode *parent = node;
	BinTreeIntNode *s = node;
	
	while (current != NULL) {
		parent = s;
		s = current;
		current = current -> left;
	}
	if (s != node -> right) {
		parent -> left = s -> right;
		s -> right = node -> right;
	}
	return s;
}

bool treeNodeDelete(BinTreeIntNode *root, int key) {
	BinTreeIntNode *current = root;
	BinTreeIntNode *parent = root;
	bool isLeftChild = true;

	while (current -> key != key) {
		parent = current;
		if (key < current -> key) {
			current = current -> left;
			isLeftChild = true;
		} else {
			current = current -> right;
			isLeftChild = false;
		}
		if (current == NULL)
			return false;
	}

	if (current -> left == NULL && current -> right == NULL) {
		if (current == root)
			root = NULL;
		else if (isLeftChild)
			parent -> left = NULL;
		else
			parent -> right = NULL;
	}
	else if (current -> right == NULL) {
		if (isLeftChild)
			parent -> left = current -> left;
		else
			parent -> right = current -> left;
	}
	else if (current -> left == NULL) {
		if (isLeftChild)
			parent -> left = current -> right;
		else
			parent -> right = current ->right;
	}
	else {
		BinTreeIntNode *successor = getSuccessor(current);
		if (current == root)
			root = successor;
		else if (isLeftChild)
			parent -> left = successor;
		else
			parent -> right = successor;
		successor -> left = current -> left;
	}
	return true;
}

int subTreeCount(BinTreeIntNode *node) {
	if (!node)
		return 0;
	printf("%d ", node -> key);
	if (node -> left == NULL && node -> right == NULL)
		return 1;
	else {
		int c;
		c = 1 + subTreeCount(node -> left) + subTreeCount(node -> right);
		return c;
	}
}

bool isBalanced(BinTreeIntNode *root) {
	if (!root)
		return false;
	int lc;		// Left subtree counter
	int rc;		// Right subtree counter
	
	if (root -> left)
		lc = subTreeCount(root -> left);
	else
		lc = 0;
	
	if (root -> right)
		rc = subTreeCount(root -> right);
	else
		rc = 0;
	
	printf("lc: %d, rc: %d\n", lc, rc);
	return (abs(lc - rc) <= 1);
}

BinTreeIntNode* balancedTree(int n) {
	BinTreeIntNode *newNode;
	int x;
	int nL;
	int nR;
	if (n == 0) {
		return NULL;
	} else {
		fscanf(file, "%d", &x);
		nL = n / 2;
		nR = n - nL - 1;
		newNode = (BinTreeIntNode*) malloc(sizeof(BinTreeIntNode));
		newNode -> key = x;
		newNode -> left = balancedTree(nL);
		newNode -> right = balancedTree(nR);
	}
	return newNode;
}

void balanceTest() {
	BinTreeIntNode *tree = NULL;
	file = fopen("../data/balance.txt", "r");
	if (file == NULL) {
		printf("%s \n", "Cannot open file");
		return;
	}
	const int count = 15;
	tree = balancedTree(count);
	fclose(file);
	//printBinTree(tree);
	printf("%d\n", isBalanced(tree));
}

int main(int argc, char** args) {
	srand(time(NULL));
	// The size or array.
	#define ARSIZE 5
	// The number of elements in every tree
	const int NODES = 10;
	// The random values will be generated in range 0 < r < BORDER
	const int BORDER = 100; 
	BinTreeIntNode *bt[ARSIZE];
	bt[0] = treeInsert(NULL, 10);
	treeInsert(bt[0], 11);
	treeInsert(bt[0], 12);
	treeInsert(bt[0], 7);
	treeInsert(bt[0], 8);
	treeInsert(bt[0], 5);
	printBinTree(bt[0]);


	// Populating the tree with random values
	for (int i = 0; i < ARSIZE; ++i) {
		bt[i] = treeInsert(NULL, 10 + i);
	}

//	BinTreeIntNode *tree = treeInsert(tree, 10);
//  treeInsert(tree, 8);
//  treeInsert(tree, 19);
//  treeInsert(tree, 5);
//  treeInsert(tree, 9);
//  treeInsert(tree, 16);
//  treeInsert(tree, 21);
//  treeInsert(tree, 3);
//  treeInsert(tree, 24);
//  printBinTree(tree);
//  printf(" \n");
//	printf("%d\n", isBalanced(tree));
//
//  treeNodeDelete(tree, 5);
//  treeNodeDelete(tree, 9);
//  printBinTree(tree);
//	printf("%d\n", isBalanced(tree));
  //printf(" \n");
  //treeNodeDelete(tree, 19);
  //printBinTree(tree);
  //printf(" \n");
  //treeNodeDelete(tree, 8);
  //printBinTree(tree);
  //printf(" \n");

	//balanceTest();
  printf(" \n");
	return EXIT_SUCCESS;
}
