#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define MAX_SIZE (50)
#define MAX_LINE (1024)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

Student* AllocateMemoryAndReadStudents(int noRows);

int main()
{
	int noRows = 0;
	
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };


	filePointer = fopen("Student.txt", "r");
	if (!filePointer) { //isto kao ==NULL
		printf("File isn't opened! \n");
		return -1;
	}
	while (!feof(filePointer))
	{
		fgets(buffer, MAX_LINE, filePointer);
		noRows++;
	}
	//printf("%d", noRows);

	Student* studenti;

	studenti = (Student*)malloc(noRows * sizeof(Student));

	if (!studenti) {
		printf("Memory allocation failed.\n");
		return NULL;
	}

	fclose(filePointer);

	return 0;
}

Student* AllocateMemoryAndReadStudents(int noRows) {

}