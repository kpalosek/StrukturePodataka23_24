/*Napisati program koji omogucava rad s binarnim stablom pretrazivanja. Treba omoguciti unosenje
novog elementa u stablo, ispis elemenata (inorder, preorder, postorder i level order), brisanje i
pronalazenje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#include <stdio.h>
#include <stdlib.h>

struct binaryTree;
typedef struct binaryTree* Position;
typedef struct binaryTree {
	int value;
	Position left;
	Position right;
}binaryTree;

struct queue;
typedef struct queue* queuePosition;
typedef struct queue {
	Position treeNode;
	queuePosition nextNode;
}Queue;

Position createElement(int value);
Position addElement(Position root, int value);
Position findElement(Position root, int value);
int printInorder(Position root);
int printPreorder(Position root);
int printPostorder(Position root);
int printLevelOrder(Position root, queuePosition headQ);
int push(queuePosition headQ, Position currNode);
int pop(queuePosition headQ);
queuePosition findLast(queuePosition headQ);
queuePosition findPrev(queuePosition headQ, int value);
Position deleteElement(Position root, int value);
int deleteTree(Position root);

int main()
{
	Position root = NULL;
	Position temp = NULL;
	Queue HeadQ = { .treeNode = NULL, .nextNode = NULL };
	int input = 0;
	int value = 0;

	while (1) {
		printf("___________________________________\n\n");
		printf("(1) Add element\n(2) Find element\n(3) Print inorder\n(4) Print preorder\n(5) Print postorder\n(6) Print level order\n(7) Delete element\n(8) Delete tree\n(9) Exit\n");
		printf("___________________________________\n");
		if (scanf("%d%*c", &input) != 1) {
			printf(RED "Invalid input.\n" RESET);
			break;
		}

		switch (input)
		{
			case 1:
				printf("Enter value: ");
				if (scanf("%d%*c", &value) != 1) {
					printf(RED "Value is not an integer.\n" RESET);
					break;
				}
				root = addElement(root, value);
				if (root == NULL) {
					printf(RED "Element was not created.\n" RESET);
				}
				break;
			case 2:
				printf("Enter value: ");
				if (scanf("%d%*c", &value) != 1) {
					printf(RED "Value is not an integer.\n" RESET);
					break;
				}
				temp = findElement(root, value);
				if (temp != NULL) {
					printf(GREEN "Element %d was found.\n" RESET, temp->value);
				}
				else {
					printf(RED "Element %d was not found.\n" RESET, value);
				}
				break;
			case 3:
				printf(YELLOW "Inorder: " RESET);
				printInorder(root);
				printf("\n");
				break;
			case 4:
				printf(YELLOW "Preorder: " RESET);
				printPreorder(root);
				printf("\n");
				break;
			case 5:
				printf(YELLOW "Postorder: " RESET);
				printPostorder(root);
				printf("\n");
				break;
			case 6:
				printf(YELLOW "Level-order: " RESET);
				printLevelOrder(root, &HeadQ);
				printf("\n");
				break;
			case 7:
				printf("Enter value: \n");
				if (scanf("%d%*c", &value) != 1) {
					printf(RED "Value is not an integer.\n" RESET);
				}
				root = deleteElement(root, value);
				break;
			case 8:
				deleteTree(root);
				root = NULL;
				printf(GREEN "Binary search tree deleted.\n" RESET);
				break;
			case 9:
				return EXIT_SUCCESS;
			default:
				printf(RED "Invalid input.\n" RESET);
				break;
		}
	}
	
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

	printf("Failed to allocate memory.\n");
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

Position findElement(Position root, int value)
{
	if (root == NULL) {
		return NULL;
	}
	else if (value < root->value) {
		return findElement(root->left, value);
	}
	else if (value > root->value) {
		findElement(root->right, value);
	}
	else {
		return root;
	}
}

int printInorder(Position root)
{
	if (root == NULL) {
		return EXIT_SUCCESS;
	}
	
	printInorder(root->left);
	printf("%d ", root->value);
	printInorder(root->right);

	return EXIT_SUCCESS;
}

int printPreorder(Position root)
{
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	printPreorder(root->left);
	printPreorder(root->right);
	printf("%d ", root->value);

	return EXIT_SUCCESS;
}

int printPostorder(Position root)
{
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	printf("%d ", root->value);
	printPostorder(root->left);
	printPostorder(root->right);

	return EXIT_SUCCESS;
}

int push(queuePosition headQ, Position currNode)
{
	queuePosition newElement = NULL;
	newElement = (queuePosition)malloc(sizeof(Queue));

	if (newElement) {
		newElement->treeNode = currNode;
		newElement->nextNode = headQ->nextNode;
		headQ->nextNode = newElement;
		return EXIT_SUCCESS;
	}

	printf(RED "Failed to allocate memory.\n" RESET);
	return EXIT_FAILURE;
}

int pop(queuePosition headQ)
{
	queuePosition last = NULL;
	queuePosition prev = NULL;
	queuePosition temp = NULL;
	
	last = findLast(headQ);
	if (last) {
		prev = findPrev(headQ, last->treeNode->value);
		if (prev) {
			prev->nextNode = last->nextNode;
			free(last);
			return EXIT_SUCCESS;
		}
	}

	return EXIT_FAILURE;
}

queuePosition findLast(queuePosition headQ)
{
	queuePosition curr = headQ;

	if (curr == NULL) {
		printf(RED "Queue is empty.\n" RESET);
		return NULL;
	}

	while (curr->nextNode != NULL) {
		curr = curr->nextNode;
	}

	return curr;
}

queuePosition findPrev(queuePosition headQ, int value)
{
	queuePosition current = headQ;

	while (current->nextNode) {
		if (current->nextNode->treeNode->value == value) {
			return current;
		}
		current = current->nextNode;
	}

	printf(RED "Unable to delete element from queue.\n" RESET);
	return NULL;
}

int printLevelOrder(Position root, queuePosition headQ)
{
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	push(headQ, root);
	queuePosition curr = NULL;
	Position current = NULL;

	while (headQ->nextNode != NULL) {
		curr = findLast(headQ);
		current = curr->treeNode;
		printf(" %d", current->value);
		pop(headQ);

		if (current->left != NULL) {
			push(headQ, current->left);
		}
		if (current->right != NULL) {
			push(headQ, current->right);
		}
	}

	return EXIT_SUCCESS;
}

Position deleteElement(Position root, int value)
{
	if (root == NULL) {
		printf(RED "Element %d does not exist\n" RESET, value);
		return root;
	}

	if (root->value > value) {
		root->left = deleteElement(root->left, value);
		return root;
	}
	else if (root->value < value) {
		root->right = deleteElement(root->right, value);
		return root;
	}

	if (root->left == NULL) {
		Position temp = root->right;
		free(root);
		printf(GREEN "Node deleted.\n" RESET);
		return temp;
	}
	else if (root->right == NULL) {
		Position temp = root->left;
		free(root);
		printf(GREEN "Node deleted.\n" RESET);
		return temp;
	}
	else {
		Position newNode = root;
		Position new = root->right;
		while (new->left != NULL) {
			newNode = new;
			new = new->left;
		}
		if (newNode != root) {
			newNode->left = new->right;
		}
		else {
			newNode->right = new->right;
		}
		root->value = new->value;
		free(new);
		printf(GREEN "Node deleted.\n" RESET);
		return root;
	}
}

int deleteTree(Position root)
{
	if (root == NULL) {
		return EXIT_SUCCESS;
	}

	deleteTree(root->left);
	deleteTree(root->right);

	free(root);

	return EXIT_SUCCESS;
}