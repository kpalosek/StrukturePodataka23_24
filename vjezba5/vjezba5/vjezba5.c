#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)
#define FILE_NAME_LENGTH (20)

struct stack;
typedef struct stack* Position;
typedef struct stack {
	double value;
	Position next;
}Stack;

int readFile(Position head, char* fileName);
int readFromBuffer(Position head, char* buffer);
Position createNewElement(double value);
int push(Position head, double value);
int pop(Position head, double* value);
int performOperation(Position head, char operation);
int deleteElement(Position head);
int getResult(Position head, double* result);
int checkValid(Position head);

int main()
{	
	Stack head = { .value = 0, .next = NULL };
	char fileName[FILE_NAME_LENGTH] = "postfix.txt";
	double result = 0.0;

	readFile(&head, fileName);

	if(getResult(&head, &result) == EXIT_SUCCESS && checkValid(&head) == EXIT_SUCCESS )
		printf("The result is: %.2lf", result);

	return EXIT_SUCCESS;
}

int readFile(Position head, char* fileName)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* filePointer = NULL;

	filePointer = fopen(fileName, "r");

	if (!filePointer) {
		printf("File failed to open.\n");
		return EXIT_FAILURE;
	}

	if (fgets(buffer, MAX_LINE, filePointer)) {
		readFromBuffer(head, buffer);
	}
	else{
		printf("Failed to get data from file.\n");
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int readFromBuffer(Position head, char* buffer)
{
	int numBytes = 0;
	double value = 0;
	char operation = ' ';


	while (strlen(buffer) > 0)
	{
		if (sscanf(buffer, "%lf %n", &value, &numBytes) == 1)
		{
			push(head, value);
		}
		else
		{
			if (sscanf(buffer, "%c %n", &operation, &numBytes) == 1) {
				performOperation(head, operation);
			}
		}

		buffer += numBytes;
	}

	return EXIT_SUCCESS;
}

Position createNewElement(double value)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Stack));

	if (newElement) {
		newElement->value = value;
		return newElement;
	}

	printf("Failed to allocate memory.\n");
	return NULL;
}


int push(Position head, double value)
{
	Position current = head;
	Position newElement = NULL;

	newElement = createNewElement(value);

	if (newElement) {
		newElement->next = current->next;
		current->next = newElement;
		
		return EXIT_SUCCESS;
	}

	printf("Failed to create new element.\n");
	return EXIT_FAILURE;
}

int pop(Position head, double* value)
{
	Position current = head;
	Position temp = NULL;

	if (current->next) {
		*value = current->next->value;
		deleteElement(head);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

int performOperation(Position head, char operation)
{
	double value1 = 0, value2 = 0;

	pop(head, &value1);
	pop(head, &value2);

	switch (operation)
	{
	case '+':
		push(head, value2 + value1);
		break;
	case '-':
		push(head, value2 - value1);
		break;
	case '*':
		push(head, value2 * value1);
		break;
	case '/':
		push(head, value2 / value1);
		break;
	default:
		printf("Unknown operation.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int deleteElement(Position head)
{
	Position temp = NULL;
	
	if (head->next) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
		
		return EXIT_SUCCESS;
	}

	printf("Stack is empty.\n");
	return EXIT_FAILURE;
}

int getResult(Position head, double* result)
{
	if (head->next) {
		*result = head->next->value;
		deleteElement(head);
		return EXIT_SUCCESS;
	}

	printf("Failed to get the result.\n");

	return EXIT_FAILURE;
}

int checkValid(Position head)
{
	if (head->next) {
		printf("Invalid postfix expression.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}