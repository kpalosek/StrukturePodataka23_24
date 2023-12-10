/*Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i
povratak u prethodni direktorij. Tocnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME (50)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct directory;
typedef struct directory* Position_dir;
typedef struct directory {
	char name[MAX_NAME];
	Position_dir subdirectories;
	Position_dir next;
}Directory;

struct stack;
typedef struct stack* Position_stack;
typedef struct stack {
	Position_dir directory;
	Position_stack next;
}Stack;

int push(Position_stack headS, Position_dir current_dir);
int pop(Position_stack headS);
Position_dir createDirectory(char* name);
Position_dir changeDirectory(Position_dir current_dir, char* name);
int addDirectory(Position_dir current_dir, char* name);
int printDirectory(Position_dir current_dir);

int main()
{
	Directory headDir = { .name = { 0 }, .subdirectories = NULL, .next = NULL };
	Stack headS = { .directory = NULL, .next = NULL };
	char input[MAX_NAME] = " ";
	char name[MAX_NAME] = " ";

	Position_dir current_directory;
	Position_dir temp = NULL;
	Position_dir root = (Position_dir)malloc(sizeof(Directory));					//stvaramo pocetak stabla kao C:/
	strcpy(root->name, "C:/");
	root->subdirectories = NULL;
	root->next = NULL;
	headDir.next = root;

	current_directory = root;
	push(&headS, current_directory);					//dodajemo na stog pocetni direktorij u kojem se nalazimo po defaultu

	while (1) {
		printf("\nmd | cd dir | cd.. | dir | exit (e)\n");
		scanf("%[^\n]%*c", input);

		if (strcmp("md", input) == 0) {
			printf("Enter directory name: ");
			scanf("%[^\n]%*c", name);
			addDirectory(current_directory, name);
		}
		else if (strcmp("cd dir", input) == 0) {
			printf("Enter direcotory name: ");
			scanf("%[^\n]%*c", name);
			temp = changeDirectory(current_directory, name);
			if (temp) {
				current_directory = temp;
				push(&headS, current_directory);
			}
			else {
				printf("Directory %s not found.\n", name);
			}
		}
		else if (strcmp("cd..", input) == 0) {
			if (pop(&headS) == EXIT_SUCCESS) {
				current_directory = headS.next->directory;
			}
		}
		else if (strcmp("dir", input) == 0) {
			printDirectory(current_directory);
		}
		else if (strcmp("e", input) == 0) {
			return EXIT_SUCCESS;
		}
		else {
			printf("Unknown command.\n");
		}
	}

	return EXIT_SUCCESS;
}

int push(Position_stack headS, Position_dir current_dir)
{
	Position_stack newDir = NULL;
	newDir = (Position_stack)malloc(sizeof(Stack));

	if (newDir) {										//kada udjemo u novi direktorij dodajemo ga na pocetak stoga
		newDir->directory = current_dir;
		newDir->next = headS->next;
		headS->next = newDir;

		return EXIT_SUCCESS;
	}

	printf("Failed to allocate memory.\n");

	return EXIT_FAILURE;
}

int pop(Position_stack headS)
{
	Position_stack temp = NULL;

	if (headS->next->next == NULL) {					//provjeramo ima li na stogu ista osim C:/
		printf("Already in C:/\n");
		return EXIT_FAILURE;
	}

	temp = headS->next;									//ako na stogu postoji nesto osim C:/ micemo sa stoga zadnje dodan direktorij
	headS->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

Position_dir createDirectory(char* name)
{
	Position_dir newDirecory = NULL;
	newDirecory = (Position_dir)malloc(sizeof(Directory));

	if (newDirecory) {
		strcpy(newDirecory->name, name);
		newDirecory->subdirectories = NULL;
		newDirecory->next = NULL;

		return newDirecory;
	}

	printf("Failed to allocate memory.\n");

	return NULL;
}

int addDirectory(Position_dir current_dir, char* name)
{
	Position_dir newDirectory = NULL;
	newDirectory = createDirectory(name);

	if (newDirectory) {
		newDirectory->next = current_dir->subdirectories;
		current_dir->subdirectories = newDirectory;

		return EXIT_SUCCESS;
	}

	printf("Failed to create new directory.\n");

	return EXIT_FAILURE;
}

int printDirectory(Position_dir current_dir)
{
	Position_dir curr = current_dir->subdirectories;

	if (!curr) {
		printf("empty\n");
		return EXIT_FAILURE;
	}

	while (curr) {
		printf("%s   ", curr->name);
		curr = curr->next;
	}

	return EXIT_SUCCESS;
}

Position_dir changeDirectory(Position_dir current_dir, char* name)
{
	Position_dir curr = current_dir->subdirectories;

	while (curr) {
		if (strcmp(curr->name, name) == 0) {
			return curr;
		}
		curr = curr->next;
	}

	return NULL;
}