#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (20)
#define MAX_LINE (1024)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX];
	char surname[MAX];
	int birthYear;
	Position Next;
}Person;

int mainMenu(Person head);
int addToFrontOfTheList(Position head);
int addToEndOfTheList(Position head);
Position createPerson();
Position findLast(Position firstEl);
int printData(Position firstEl);
Position findElement(Position firstEl);
int deleteElement(Position head);
int printElement(Position element);
Position findPrevious(Position head, char* surname);
char* getSurname(char* surname);
int addInFront(Position head);
int addBehind(Position head);
int addToFile(Position firstEl);
int readFromFile(Position head);
int getNoRows(int* noRows);
int addElementFromFile(Position head, char* name, char* surname, int birth_year);
Position createPersonFile(char* name, char* surname, int birth_year);
int deallocateList(Position head);


int main()
{
	Person head = { .name = {0}, .surname = {0} , .birthYear = 0, .Next = NULL };

	mainMenu(head);

	return EXIT_SUCCESS;
}

int mainMenu(Person head)
{
	char input = { 0 };
	Position person = NULL;

	while (1) {
		printf("\n(1) Add to the Front\t(2) Add to the End\t(3) Print data\t\t(4) Find Element\t(5) Delete element\n(6)Add in Front of\t(7) Add Behind\t\t(8) Add to File\t\t(9) Read from file\t(0) Exit Program\n");
		do {
			input = getchar(stdin);
			getchar();
			if (input != '1' && input != '2' && input != '3' && input != '4' && input != '5' && input != '6' && input != '7' && input != '8' && input != '9' && input != '0')
				printf("Invalid input.\n");
		} while (input != '1' && input != '2' && input != '3' && input != '4' && input != '5' && input != '6' && input != '7' && input != '8' && input != '9' && input != '0');


		switch (input)
		{
			case '1':
				addToFrontOfTheList(&head);
				break;
			case '2':
				addToEndOfTheList(&head);
				break;
			case '3':
				printData(head.Next);
				break;
			case '4':
				person = findElement(head.Next);
				if (person)
					printElement(person);
				break;
			case '5':
				deleteElement(&head);
				break;
			case '6':
				addInFront(&head);
				break;
			case '7':
				addBehind(&head);
				break;
			case '8' :
				addToFile(head.Next);
				break;
			case '9':
				deallocateList(&head);
				readFromFile(&head);
				break;
			case '0':
				deallocateList(&head);
				return EXIT_SUCCESS;
			default:
				printf("Invalid input.\n");
				break;
		}
	}
	
	return EXIT_SUCCESS;
}

int addToFrontOfTheList(Position head) {
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson) {
		newPerson->Next = head->Next;
		head->Next = newPerson;
	}
	else
	{
		printf("Failed to create new person.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int addToEndOfTheList(Position head) {
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPerson();

	if (newPerson) {
		last = findLast(head);
		newPerson->Next = last->Next;
		last->Next = newPerson;
	}
	else
	{
		printf("Failed to create new person.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

Position createPerson() {

	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		printf("Memory allocation failed.\n");
		return NULL;
	}

	char temp_name[MAX] = { 0 };
	char temp_surname[MAX] = { 0 };
	int temp_birthYear = 0;

	printf("Enter name: ");
	scanf("%[^\n]%*c", temp_name);
	printf("Enter surname: ");
	scanf("%[^\n]%*c", temp_surname);
	printf("Enter birth year: ");
	scanf("%d%*c", &temp_birthYear);

	strcpy(newPerson->name, temp_name);
	strcpy(newPerson->surname, temp_surname);
	newPerson->birthYear = temp_birthYear;

	return newPerson;
}

Position findLast(Position firstEl) {
	Position current = NULL;
	current = firstEl;

	if (!current) {
		printf("The list is empty.\n");
		return NULL;
	}

	while (current->Next) {
		current = current->Next;
	}

	return current;
}

int printData(Position firstEl)
{
	Position current = NULL;
	current = firstEl;

	if (!current) {
		printf("The list is empty.\n");
		return EXIT_FAILURE;
	}

	for (; current != NULL; current = current->Next) {
		printf("\nName: %s\tSurname: %s\t\tBirth year: %d\n", current->name, current->surname, current->birthYear);
	}

	return EXIT_SUCCESS;
}

Position findElement(Position firstEl)
{
	char surname[MAX] = { 0 };
	Position current = NULL;
	current = firstEl;

	if (!current) {
		printf("List is empty.\n");
		return NULL;
	}

	strcpy(surname, getSurname(surname));

	while (current) {
		if (strcmp(surname, current->surname) == 0)
			return current;
		
		current = current->Next;
	}

	printf("Person not found.\n");

	return NULL;
}

int printElement(Position element)
{
	if (!element) {
		printf("Element does not exist.\n");
		return EXIT_FAILURE;
	}

	printf("\nName: %s\tSurname: %s\t\tBirth year: %d\n", element->name, element->surname, element->birthYear);

	return EXIT_SUCCESS;
}

int deleteElement(Position head)
{
	char surname[MAX] = { 0 };
	Position temp = NULL;
	temp = head;

	if (!(temp->Next)) {
		printf("List is empty.\n");
		return EXIT_FAILURE;
	}

	strcpy(surname, getSurname(surname));

	Position prev = NULL;
	prev = findPrevious(temp, surname);

	if (prev) {
		temp = prev->Next;
		prev->Next = temp->Next;
		free(temp);
		printf("Person deleted from list.\n");
		return EXIT_SUCCESS;
	}

	printf("Element does not exist.\n");

	return EXIT_FAILURE;
}

Position findPrevious(Position current, char* surname)
{

	while (current->Next) {
		if (strcmp(surname, current->Next->surname) == 0)
			return current;

		current = current->Next;
	}

	return NULL;
}

char* getSurname(char* surname)
{
	printf("Enter surname: ");
	scanf("%[^\n]%*c", surname);

	return surname;
}

int addInFront(Position head)
{
	char surname[MAX] = { 0 };
	Position prev = NULL;
	Position newPerson = NULL;

	if (!head->Next) {
		printf("The list is empty.\n");
		return EXIT_FAILURE;
	}

	newPerson = createPerson();

	if (newPerson) {
		strcpy(surname, getSurname(surname));
		prev = findPrevious(head, surname);

		if (prev) {
			newPerson->Next = prev->Next;
			prev->Next = newPerson;
			return EXIT_SUCCESS;
		}
		else {
			printf("Element does not exist.\n");
			return EXIT_FAILURE;
		}
	}

	return EXIT_FAILURE;
}

int addBehind(Position head)
{
	Position newPerson = NULL;
	Position current = NULL;

	if (!head->Next) {
		printf("The list is empty.\n");
		return EXIT_FAILURE;
	}

	newPerson = createPerson();

	if (newPerson) {

		current = findElement(head->Next);

		if (current) {
			newPerson->Next = current->Next;
			current->Next = newPerson;
			return EXIT_SUCCESS;
		}
		else {
			return EXIT_FAILURE;
		}
	}
	return EXIT_FAILURE;
}

int addToFile(Position firstEl)
{
	Position current = NULL;
	current = firstEl;
	FILE* filePointer = NULL;

	filePointer = fopen("data.txt", "w");

	if (!filePointer) {
		printf("File failed to open.\n");
		return EXIT_FAILURE;
	}

	if (!current) {
		printf("The list is empty.\n");
		return EXIT_FAILURE;
	}

	fprintf(filePointer, "NAME\t\tSURNAME\t\tBIRTH YEAR");

	while (current) {
		fprintf(filePointer, "\n%-8s\t%-8s\t%-4d", current->name, current->surname, current->birthYear);
		current = current->Next;
	}

	printf("Data added successfully.\n");

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int readFromFile(Position head)
{
	Position current = NULL;
	current = head;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	int noRows = 0;
	char temp_name[MAX] = { 0 };
	char temp_surname[MAX] = { 0 };
	int temp_birthYear = 0;

	if (!current) {
		printf("The list is empty.\n");
		return EXIT_FAILURE;
	}

	filePointer = fopen("data.txt", "r");

	if (!filePointer) {
		printf("File failed to open.\n");
		return EXIT_FAILURE;
	}

	noRows = getNoRows(&noRows);

	fgets(buffer, MAX_LINE, filePointer);

	for (int i = 0; i < noRows; i++) {
		fscanf(filePointer, "%s %s %d", temp_name, temp_surname, &temp_birthYear);
		addElementFromFile(head, temp_name, temp_surname, temp_birthYear);
	}

	printf("Data added successfully.\n");

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int getNoRows(int* noRows)
{
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("data.txt", "r");

	if (!filePointer) {
		printf("File failed to open.\n");
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, filePointer);

	while (!feof(filePointer)) {
		fgets(buffer, MAX_LINE, filePointer);
		(*noRows)++;
	}

	fclose(filePointer);

	return *noRows;
}

int addElementFromFile(Position head, char* name, char* surname, int birth_year)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = createPersonFile(name, surname, birth_year);

	if (newPerson) {
		last = findLast(head);
		newPerson->Next = last->Next;
		last->Next = newPerson;
	}
	else
	{
		printf("Failed to create new person.\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

Position createPersonFile(char* name, char* surname, int birth_year)
{
	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {
		printf("Memory allocation failed.\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birth_year;

	return newPerson;
}

int deallocateList(Position head)
{
	Position temp = NULL;
	Position current = head;

	while (current->Next != NULL) {
		temp = current->Next;
		current->Next = temp->Next;
		free(temp);
	}
	
	return EXIT_SUCCESS;
}