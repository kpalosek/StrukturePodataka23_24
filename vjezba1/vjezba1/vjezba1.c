#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define MAX_POINTS (30)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int getNoRows(FILE *filePointer);
Student* allocateMemory(int noRows);
int readFile(int noRows, FILE *filePointer, Student* studenti);
int printData(int noRows, Student* studenti);
double getRelativePoints(Student* student);

int main()
{
	FILE* filePointer = NULL;

	filePointer = fopen("Student.txt", "r");
	if (!filePointer) {
		printf("File failed to open.\n");
		return -1;
	}

	int noRows = getNoRows(filePointer); //iz datoteke citamo broj studenanta
	
	Student* studenti = NULL;
	studenti = allocateMemory(noRows); //alociramo memoriju potrebnu za noRows studenata

	readFile(noRows, filePointer, studenti); //citamo podatke iz datoteke i sprememo ih u strukturu
	printData(noRows, studenti); //ispisujemo podatke

	fclose(filePointer);
	free(studenti);

	return 0;
}

int getNoRows(FILE* filePointer)
{
	int noRows = 0;
	char buffer[MAX_LINE] = { 0 };

	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		noRows++;
	}
	rewind(filePointer);

	return noRows;
}

Student* allocateMemory(int noRows)
{
	Student* studenti = NULL;
	studenti = (Student*)malloc(noRows * sizeof(Student));

	if (!studenti) {
		printf("Unsuccessful allocation.\n");
		return NULL;
	}

	return studenti;
}

int readFile(int noRows, FILE* filePointer, Student* studenti)
{
	for (int i = 0; i < noRows; i++)
		fscanf(filePointer, "%s %s %lf%*c", studenti[i].name, studenti[i].surname, &studenti[i].points);

	return EXIT_SUCCESS;
}

double getRelativePoints(Student *student)
{
	return (float)student->points / MAX_POINTS * 100;
}

int printData(int noRows, Student* studenti)
{
	printf("NAME\t\tSURNAME\t\tPOINTS\t\tRELATIVE POINTS\n\n");
	for (int i = 0; i < noRows; i++) {
		printf("%s\t\t%s\t\t%.2lf\t\t%.2lf\n", studenti[i].name, studenti[i].surname, studenti[i].points, getRelativePoints(&studenti[i]));
	}

	return EXIT_SUCCESS;
}