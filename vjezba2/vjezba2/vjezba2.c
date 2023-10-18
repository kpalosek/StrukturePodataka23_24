#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[20];
	char surname[20];
	int birthYear;
	Position Next;
}Person;

int addToFrontOfTheList(Position head);
int addToEndOfTheList(Position head);
Position createPerson();
Position findLast(Position head);


int main()
{
	Person head = { .name = {0}, .surname = {0} , .birthYear = {0}, .Next = NULL };

	return 0;
}

int addToFrontOfTheList(Position head) {
	Position newPerson = NULL;

	newPerson = createPerson();

	if (newPerson) {
		newPerson->Next = head->Next;
		head->Next = newPerson;
	}

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
}

Position createPerson() {

}

Position findLast() {

}