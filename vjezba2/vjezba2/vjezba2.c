#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX (20)

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
int deleteElement(Position firstEl);
int printElement(Position element);


int main()
{
	Person head = { .name = {0}, .surname = {0} , .birthYear = {0}, .Next = NULL };

	mainMenu(head);

	return EXIT_SUCCESS;
}

int mainMenu(Person head)
{
	char input = { 0 };
	Position person = NULL;

	while (1) {
		printf("\n(1) Add to the Front\t(2) Add to the End\t(3) Print Data\t(4) Find Element\t(5) Delete element\t\t(6)Exit Program\n");
		do {
			input = getchar(stdin);
			getchar();
			if (input != '1' && input != '2' && input != '3' && input != '4')
				printf("Invalid input.\n");
		} while (input != '1' && input != '2' && input != '3' && input != '4');


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
	scanf("%s", temp_name);
	printf("Enter surname: ");
	scanf(" %s", temp_surname);
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

	free(current);

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

	printf("Enter surname: ");
	scanf("%s", surname);

	while (current->Next) {
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

int deleteElement(Position firstEl)
{
	char surname[MAX] = { 0 };
	Position current = NULL;
	current = firstEl;

	if (!current) {
		printf("List is empty.\n");
		return NULL;
	}

	printf("Enter surname: ");
	scanf("%s", surname);

}
