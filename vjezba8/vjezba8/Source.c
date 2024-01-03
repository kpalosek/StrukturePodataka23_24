#define _CRT_SECURE_NO_WARNINGS
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct binaryTree;
typedef struct binaryTree* Position;
typedef struct binaryTree {
	int value;
	Position left;
	Position right;
}binaryTree;

Position createElement(int value);
Position addElement(Position root, int value);
int printInorder(Position root);
int subtreeSum(Position root, int oldValue);
int addToFile(Position root);
int printToFileInorder(Position root, FILE* filePointer);

int main()
{
	Position root = NULL;
	root = addElement(root, 2);
	root = addElement(root, 5);
	root = addElement(root, 1);
	root = addElement(root, 7);
	root = addElement(root, 4);
	root = addElement(root, 8);
	root = addElement(root, 2);
	root = addElement(root, 11);
	root = addElement(root, 7);
	root = addElement(root, 3);

	printf(YELLOW "\nInorder before change: \n" RESET);
	printInorder(root);
	addToFile(root);

	subtreeSum(root, 0);

	printf(YELLOW "\nInorder after change: \n" RESET);
	printInorder(root);
	addToFile(root);

	srand(time(NULL));
	int temp_val = 0;
	Position rootRand = NULL;

	for (int i = 0; i < 10; i++)
	{
		temp_val = (rand() % (90 - 10 + 1)) + 10;
		rootRand = addElement(rootRand, temp_val);
	}

	printf(YELLOW "\nInorder before change random tree: \n" RESET);
	printInorder(rootRand);
	addToFile(rootRand);

	subtreeSum(rootRand, 0);

	printf(YELLOW "\nInorder after change random tree: \n" RESET);
	printInorder(rootRand);
	addToFile(rootRand);

	printf("\n\n");

	return EXIT_SUCCESS;
}

Position createElement(int value)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(binaryTree));

	if (newElement) {
		newElement->value = value;
		newElement->left = NULL;
		newElement->right = NULL;

		return newElement;
	}

	printf(RED "Failed to allocate memory.\n" RESET);
	
	return NULL;
}

Position addElement(Position root, int value)
{
	if (root == NULL) {
		return createElement(value);
	}
	else if (value < root->value) {
		root->left = addElement(root->left, value);
	}
	else if (value >= root->value) {
		root->right = addElement(root->right, value);
	}

	return root;
}

int printInorder(Position root)
{
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	printInorder(root->left);
	printf(" %d", root->value);
	printInorder(root->right);

	return EXIT_SUCCESS;
}

int subtreeSum(Position root, int oldValue)
{
	if (root == NULL) {
		return 0;
	}

	oldValue = root->value;

	root->value = subtreeSum(root->left, 0) + subtreeSum(root->right, 0);

	return oldValue + root->value;
}

int addToFile(Position root)
{
	FILE* filePointer = NULL;
	filePointer = fopen("data.txt", "a");

	if (!filePointer) {
		printf(RED "File failed to open.\n" RESET);
		return EXIT_FAILURE;
	}

	printToFileInorder(root, filePointer);
	fprintf(filePointer, "\n");

	fclose(filePointer);
	return EXIT_SUCCESS;
}

int printToFileInorder(Position root, FILE* filePointer)
{
	if (root == NULL) {
		return 0;
	}

	printToFileInorder(root->left, filePointer);
	fprintf(filePointer, " %d", root->value);
	printToFileInorder(root->right, filePointer);

	return EXIT_SUCCESS;
}