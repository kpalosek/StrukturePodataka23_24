#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (1024)

struct _Polynome;
typedef struct _Polynome* Position;
typedef struct _Polynome {
	int coefficient;
	int exponent;
	Position next;
}Polynome;

int readFromFile(Position headPoly1, Position headPoly2);
int readFromBuffer(Position headPoly, char* buffer);
int addToList(Position headPoly, int coefficient, int exponent);
Position createElement(int coefficient, int exponent);
int printData(Position firstEl);
Position findPrevious(Position head, int coefficient, int exponent);
int sumPolynomes(Position headPolySum, Position FirstPoly1, Position FirstPoly2);
int deleteEmpty(Position current, Position headPoly);

int main()
{
	Polynome headPoly1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynome headPoly2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynome headPolySum = { .coefficient = 0, .exponent = 0, .next = NULL };

	if (readFromFile(&headPoly1, &headPoly2) == 0) {
		printf("Polynome 1:\n");
		printData(headPoly1.next);
		printf("Polynome 2:\n");
		printData(headPoly2.next);
		printf("Summed polynomes:\n");
		sumPolynomes(&headPolySum, headPoly1.next, headPoly2.next);
		printData(headPolySum.next);
	}

	return EXIT_SUCCESS;
}

int readFromFile(Position headPoly1, Position headPoly2)
{
	char buffer[MAX_LINE] = { 0 };
	FILE* filePointer = NULL;
	filePointer = fopen("polynomes.txt", "r");

	if (!filePointer) {
		printf("File failed to open.\n");
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, filePointer);
	readFromBuffer(headPoly1, buffer);

	fgets(buffer, MAX_LINE, filePointer);
	readFromBuffer(headPoly2, buffer);

	return EXIT_SUCCESS;
}

int readFromBuffer(Position headPoly, char* buffer)
{
	int temp_coeff = 0;
	int temp_exp = 0;
	int check = 0;
	int status = 0;

	while(strlen(buffer)>0){
		status = sscanf(buffer, "%dx^%d %n", &temp_coeff, &temp_exp, &check);
		
		if (status != 2) {
			printf("Invalid data format in file.\n");
			return EXIT_FAILURE;
		}

		addToList(headPoly, temp_coeff, temp_exp);

		buffer += check;
	}

	return EXIT_SUCCESS;
}

int addToList(Position headPoly, int temp_coeff, int temp_exp)
{
	Position current = NULL;
	Position newElement = NULL;
	Position temp = NULL;
	Position prev = NULL;
	newElement = createElement(temp_coeff, temp_exp);

	current = headPoly;

	if (newElement) {
		while (current->next && current->next->exponent >= newElement->exponent) {
			current = current->next;
		}

		if (current->exponent == newElement->exponent) {
			current->coefficient = current->coefficient + newElement->coefficient;

			if (current->coefficient == 0) {
				deleteEmpty(current, headPoly);
			}
			free(newElement);
		}
		else {
			newElement->next = current->next;
			current->next = newElement;
		}

		return EXIT_SUCCESS;
	}
	
	return EXIT_FAILURE;
}

Position createElement(int coefficient, int exponent)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(Polynome));

	if (newElement) {
		newElement->coefficient = coefficient;
		newElement->exponent = exponent;
		return newElement;
	}

	printf("Failed to allocate memory.\n");
	return NULL;
}

int printData(Position firstEl)
{
	Position current = NULL;
	current = firstEl;

	if (!current) {
		printf("The list is empty.\n");
		return EXIT_FAILURE;
	}

	while (current) {
		if (current->exponent == 0) {
			printf("%d", current->coefficient);
			if (current->next && current->next->coefficient > 0) {
				printf(" + ");
			}
		}
		else if (current->exponent == 1) {
			printf("%dx", current->coefficient);
			if (current->next && current->next->coefficient > 0) {
				printf(" + ");
			}
		}
		else {
			printf("%dx^%d", current->coefficient, current->exponent);
			if (current->next && current->next->coefficient > 0) {
				printf(" + ");
			}
		}
		current = current->next;
	}

	printf("\n");

	return EXIT_SUCCESS;
}

Position findPrevious(Position head, int coefficient, int exponent)
{
	Position current = NULL;
	current = head;

	if (!current->next) {
		printf("Previous element does not exist.\n");
		return NULL;
	}

	while (current->next->coefficient != coefficient || current->next->exponent != exponent) {
		current = current->next;
	}

	return current;
}

int deleteEmpty(Position current, Position headPoly)
{
	Position temp = NULL;
	Position prev = NULL;

	prev = findPrevious(headPoly, current->coefficient, current->exponent);
	temp = current;
	prev->next = current->next;
	free(temp);

	return EXIT_SUCCESS;
}

int sumPolynomes(Position headPolySum, Position FirstPoly1, Position FirstPoly2)
{
	Position current = NULL;
	current = FirstPoly1;

	if (!current) {
		printf("Polynome 1 is empty.\n");
	}

	while (current) {
		addToList(headPolySum, current->coefficient, current->exponent);
		current = current->next;
	}

	current = FirstPoly2;

	if (!current) {
		printf("Polynome 2 is empty.\n");
	}

	while (current) {
		addToList(headPolySum, current->coefficient, current->exponent);
		current = current->next;
	}

	return EXIT_SUCCESS;
}