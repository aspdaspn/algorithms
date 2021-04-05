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
		if (current = NULL)
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


int main(int argc, char** args) {
	BinTreeIntNode *tree = treeInsert(tree, 10);
  treeInsert(tree, 8);
  treeInsert(tree, 19);
  treeInsert(tree, 5);
  treeInsert(tree, 9);
  treeInsert(tree, 16);
  treeInsert(tree, 21);
  printBinTree(tree);
  printf(" \n");

  treeNodeDelete(tree, 5);
  printBinTree(tree);
  printf(" \n");
  treeNodeDelete(tree, 19);
  printBinTree(tree);
  printf(" \n");
  treeNodeDelete(tree, 8);
  printBinTree(tree);
  printf(" \n");
	return EXIT_SUCCESS;
}
