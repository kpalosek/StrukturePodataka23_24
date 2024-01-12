#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RESET "\033[0m"
#define RED "\033[31m"
#define YELLOW  "\033[33m"
#define MAX_LENGTH (50)
#define MAX_BUFFER (1024)
#define countriesFile "countries.txt"

struct cityTree;
typedef struct cityTree* cityPosition;
typedef struct cityTree {
    char cityName[MAX_LENGTH];
    int population;
    cityPosition left;
    cityPosition right;
}cityTree;

struct countryList;
typedef struct countryList* countryPosition;
typedef struct countryList {
    char countryName[MAX_LENGTH];
    char fileName[MAX_LENGTH];
    cityPosition cityRoot;
    countryPosition next;
}countryList;

struct cityList;
typedef struct cityList* cityListPosition;
typedef struct cityList {
    char cityName[MAX_LENGTH];
    int population;
    cityListPosition next;
}cityList;

struct countryTree;
typedef struct countryTree* countryTreePosition;
typedef struct countryTree {
    char countryName[MAX_LENGTH];
    char fileName[MAX_LENGTH];
    cityList headCity;
    countryTreePosition left;
    countryTreePosition right;
}countryTree;

int readCountriesFromFile(char* fileName, countryPosition headCountry);
int addCountryToList(char* buffer, countryPosition headCountry);
countryPosition createCountryList(char* buffer);
int addCityTree(countryPosition country);
cityPosition addCityToTree(cityPosition cityRoot, char* cityName, int population);
cityPosition createCityTree(char* cityName, int population);
int printData_1(countryPosition firstCountry);
int printCityTreeInorder(cityPosition cityRoot);
countryTreePosition readCountriesFromFileV2(char* fileName, countryTreePosition countryRoot);
countryTreePosition addCountryTree(char* buffer, countryTreePosition countryRoot);
countryTreePosition addCountryToTree(countryTreePosition countryRoot, char* countryName, char* fileName);
countryTreePosition createCountryTree(char* countryName, char* fileName);
int addCityList(countryTreePosition country);
int addCityToList(cityListPosition cityHead, char* cityName, int population);
cityListPosition createCityList(char* cityName, int population);
int printData_2(countryTreePosition countryRoot);
int printCityList(cityListPosition firstCity);

int main()
{
    countryList headCountry = { .countryName = {0}, .fileName = {0}, .cityRoot = NULL, .next = NULL };
    countryTreePosition root = NULL;

    readCountriesFromFile(countriesFile, &headCountry);
    root = readCountriesFromFileV2(countriesFile, root);
    
    printf(YELLOW "\nLista drzava, stabla gradova\n" RESET);
    printData_1(headCountry.next);
    printf(YELLOW "\nStablo drzava, liste gradova\n" RESET);
    printData_2(root);

    return EXIT_SUCCESS;
}

int readCountriesFromFile(char* fileName, countryPosition headCountry)
{
    char buffer[MAX_BUFFER];

    FILE* filePointer = NULL;
    filePointer = fopen(fileName, "r");

    if (!filePointer) {
        printf(RED "File failed to open.\n" RESET);
        return EXIT_FAILURE;
    }

    while (!feof(filePointer)) {
        fscanf(filePointer, "%[^\n]%*c", buffer);
        addCountryToList(buffer, headCountry);
    }

    fclose(filePointer);

    return EXIT_SUCCESS;
}

int addCountryToList(char* buffer, countryPosition headCountry)
{
    countryPosition newCountryList = NULL;
    newCountryList = createCountryList(buffer);
    countryPosition current = headCountry;

    if (!newCountryList) {
        printf(RED "Failed to add country to the list." RESET);
        return EXIT_FAILURE;
    }

    //sortirano dodavanje drzave u listu

    while (current->next && strcmp(newCountryList->countryName, current->next->countryName) > 0) {
        current = current->next;
    }

    newCountryList->next = current->next;
    current->next = newCountryList;

    addCityTree(newCountryList); //stvaranje stabla gradova za trenutnu drzavu

    return EXIT_SUCCESS;
}

countryPosition createCountryList(char* buffer)
{
    char countryName[MAX_LENGTH];
    char fileName[MAX_LENGTH];
    countryPosition newCountryList = NULL;
    newCountryList = (countryPosition)malloc(sizeof(countryList));

    if (newCountryList) {
        sscanf(buffer, "%s %s", countryName, fileName);
        strcpy(newCountryList->countryName, countryName);
        strcpy(newCountryList->fileName, fileName);
        newCountryList->cityRoot = NULL;
        newCountryList->next = NULL;

        return newCountryList;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

int addCityTree(countryPosition country)
{
    char cityName[MAX_LENGTH];
    char buffer[MAX_BUFFER];
    int population;
    FILE* filePointer;

    filePointer = fopen(country->fileName, "r");
    if (!filePointer) {
        printf(RED"File failed to open.\n" RESET);
        return EXIT_FAILURE;
    }

    while (!feof(filePointer)) {
        fscanf(filePointer, "%[^\n]%*c", buffer);
        sscanf(buffer, "%[^,]%*c%d", cityName, &population);
        country->cityRoot = addCityToTree(country->cityRoot, cityName, population);
    }

    fclose(filePointer);

    return EXIT_SUCCESS;
}

cityPosition addCityToTree(cityPosition cityRoot, char* cityName, int population)
{
    if (cityRoot == NULL) {
        return createCityTree(cityName, population);
    }
    else if (population < cityRoot->population) {
        cityRoot->left = addCityToTree(cityRoot->left, cityName, population);
    }
    else if (population >= cityRoot->population) {
        cityRoot->right = addCityToTree(cityRoot->right, cityName, population);
    }

    return cityRoot;
}

cityPosition createCityTree(char* cityName, int population)
{
    cityPosition newCityTree = NULL;
    newCityTree = (cityPosition)malloc(sizeof(cityTree));

    if (newCityTree) {
        strcpy(newCityTree->cityName, cityName);
        newCityTree->population = population;
        newCityTree->left = NULL;
        newCityTree->right = NULL;

        return newCityTree;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

int printData_1(countryPosition firstCountry)
{
    countryPosition current = firstCountry;

    if (!current) {
        printf("No data entries.\n");
        return EXIT_FAILURE;
    }

    while (current) {
        printf("\n%s:\n", current->countryName);
        printCityTreeInorder(current->cityRoot);
        printf("\n");
        current = current->next;
    }

    return EXIT_SUCCESS;
}

int printCityTreeInorder(cityPosition cityRoot)
{
    if (cityRoot == NULL) {
        return EXIT_SUCCESS;
    }

    printCityTreeInorder(cityRoot->left);
    printf("\t%s, %d\n", cityRoot->cityName, cityRoot->population);
    printCityTreeInorder(cityRoot->right);

    return EXIT_SUCCESS;
}

countryTreePosition readCountriesFromFileV2(char* fileName, countryTreePosition countryRoot)
{
    char buffer[MAX_BUFFER];

    FILE* filePointer = NULL;
    filePointer = fopen(fileName, "r");

    if (!filePointer) {
        printf(RED "File failed to open.\n" RESET);
        return NULL;
    }

    while (!feof(filePointer)) {
        fscanf(filePointer, "%[^\n]%*c", buffer);
        countryRoot = addCountryTree(buffer, countryRoot);
    }

    fclose(filePointer);

    return countryRoot;
}

countryTreePosition addCountryTree(char* buffer, countryTreePosition countryRoot)
{
    char countryName[MAX_LENGTH];
    char fileName[MAX_LENGTH];

    sscanf(buffer, "%s %s%*c", countryName, fileName);

    countryRoot = addCountryToTree(countryRoot, countryName, fileName); //stvaramo binarno stablo s drzavama

    if (!countryRoot) {
        printf(RED "Failed to create new element in tree.\n" RESET);
        return NULL;
    }

    return countryRoot;
}

countryTreePosition addCountryToTree(countryTreePosition countryRoot, char* countryName, char* fileName)
{
    if (countryRoot == NULL) {
        return createCountryTree(countryName, fileName);
    }
    else if (strcmp(countryName, countryRoot->countryName) < 0) {
        countryRoot->left = addCountryToTree(countryRoot->left, countryName, fileName);
    }
    else if (strcmp(countryName, countryRoot->countryName) >= 0) {
        countryRoot->right = addCountryToTree(countryRoot->right, countryName, fileName);
    }

    return countryRoot;
}

countryTreePosition createCountryTree(char* countryName, char* fileName)
{
    countryTreePosition newCountryTree = NULL;
    newCountryTree = (countryTreePosition)malloc(sizeof(countryTree));

    if (newCountryTree) {
        strcpy(newCountryTree->countryName, countryName);
        strcpy(newCountryTree->fileName, fileName);
        strcpy(newCountryTree->headCity.cityName, "");
        newCountryTree->headCity.population = 0;
        newCountryTree->headCity.next = NULL;
        newCountryTree->left = NULL;
        newCountryTree->right = NULL;
        addCityList(newCountryTree);  //dodajemo drzavi listu gradova

        return newCountryTree;
    }
    else {
        printf(RED "Failed to allocate memory.\n" RESET);
        return NULL;
    }
}

int addCityList(countryTreePosition country)
{
    char cityName[MAX_LENGTH];
    char buffer[MAX_BUFFER];
    int population;
    FILE* filePointer;
    filePointer = fopen(country->fileName, "r");

    while (!feof(filePointer)) {
        fscanf(filePointer, "%[^\n]%*c", buffer);
        sscanf(buffer, "%[^,]%*c%d", cityName, &population);
        addCityToList(&(country->headCity), cityName, population);
    }

    fclose(filePointer);

    return EXIT_SUCCESS;
}

int addCityToList(cityListPosition headCity, char* cityName, int population)
{
    cityListPosition current = headCity;
    cityListPosition newCityList = NULL;
    newCityList = createCityList(cityName, population);

    if (!newCityList) {
        printf(RED "Failed to add city to the list.\n" RESET);
        return EXIT_FAILURE;
    }

    //sortirano dodavanje gradova po stanovnistvu

    while (current->next && current->next->population < newCityList->population) {
        current = current->next;
    }

    newCityList->next = current->next;
    current->next = newCityList;

    return EXIT_SUCCESS;
}

cityListPosition createCityList(char* cityName, int population)
{
    cityListPosition newCityList = NULL;
    newCityList = (cityListPosition)malloc(sizeof(cityList));

    if (newCityList) {
        strcpy(newCityList->cityName, cityName);
        newCityList->population = population;
        newCityList->next = NULL;

        return newCityList;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

int printData_2(countryTreePosition countryRoot)
{
    if (countryRoot == NULL) {
        return EXIT_SUCCESS;
    }

    printData_2(countryRoot->left);
    printf("\n%s:\n", countryRoot->countryName);
    printCityList(countryRoot->headCity.next);
    printData_2(countryRoot->right);

    return EXIT_SUCCESS;
}

int printCityList(cityListPosition firstCity)
{
    cityListPosition current = firstCity;

    if (!current) {
        printf("Country has no added cities.\n");
        return EXIT_FAILURE;
    }

    while (current) {
        printf("\t%s, %d\n", current->cityName, current->population);
        current = current->next;
    }

    return EXIT_SUCCESS;
}