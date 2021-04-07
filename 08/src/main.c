#include "main.h"

typedef struct Node {
	int key;
	struct Node *left;
	struct Node *right;
} BinTreeIntNode;


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

	return (abs(lc - rc) <= 1);
}

BinTreeIntNode* binSearch(BinTreeIntNode *root, int value) {
	if (root) {
		if (root -> key == value)
			return root;
		else {
			BinTreeIntNode *current = NULL;
			current = binSearch(root -> left, value);
			if (!current)
				current = binSearch(root -> right, value);
			return current;
		}
	} else
		return NULL;
}

int main(int argc, char** args) {
	// Task 1 Balanced tree
	BinTreeIntNode *tree = treeInsert(NULL, 10);
	treeInsert(tree, 5);
	treeInsert(tree, 7);
	treeInsert(tree, 3);
	treeInsert(tree, 15);
	treeInsert(tree, 25);
	treeInsert(tree, 37);
	printBinTree(tree);
	printf("\n");
	printf("The above tree is%s balanced", isBalanced(tree) ? "" : " not");
	printf("\n");

	treeInsert(tree, 47);
	treeInsert(tree, 39);
	printBinTree(tree);
	printf("\n");
	printf("The above tree is%s balanced", isBalanced(tree) ? "" : " not");
	printf("\n");
	
	// Task 2 more trees
	srand(time(NULL));
	
	// The size or array.
	#define ARSIZE 50
	
	// The number of elements in every tree
	const int NODES = 10000;
	
	// The random values will be generated in range 0 < r < BORDER
	const int BORDER = 100; 
	
	BinTreeIntNode *bt[ARSIZE];

	// Populating the trees with random values
	for (int i = 0; i < ARSIZE; ++i) {
		bt[i] = treeInsert(NULL, rand() % BORDER);
		for (int n = 0; n < NODES; ++n)
			treeInsert(bt[i], rand() % BORDER);
	}

	// Number of balanced trees
	int b = 0;

	for (int i = 0; i < ARSIZE; ++i) {
		if (isBalanced(bt[i]))
			++b;
	}
	printf("We calculated %d binary trees of %d elements. The %d%% of them were balanced.\n", 
			ARSIZE, NODES, b * 100 / ARSIZE);

	// Task 3 Binary Search
	int find = 47;

	BinTreeIntNode *f = binSearch(tree, find);
	if (f != NULL)
		printf("You searched for a value %d. We found value %d at %p address.\n", 
			find, binSearch(tree, find) -> key, binSearch(tree, find));
	else
		printf("Your value %d is not present.\n", find);

	return EXIT_SUCCESS;
}
