#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"      
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define MAX_LENGTH (50)
#define MAX_BOOKS (5)
#define MAX_BUFFER (1024)

struct bookDB;
typedef struct bookDB* bookDBPosition;          
typedef struct bookDB {                         
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    int year;
    int quantityTotal;
    int quantityAvailible;
    bookDBPosition next;
}bookDB;

struct book;
typedef struct book* bookPosition;
typedef struct book {
    char title[MAX_LENGTH];
    char author[MAX_LENGTH];
    int year;
    int quantity;
    bookPosition next;
}book;

struct user;
typedef struct user* userPosition;
typedef struct user {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    int borrowedBooks;
    book bHead;
    userPosition next;
}user;

userPosition userRegister(userPosition uHead, char* username, char* password);
userPosition createNewUser(char* username, char* password);
userPosition userLogin(userPosition uHead, char* username, char* password);
int readUsersFile(userPosition uHead);
int addBooksToUser(userPosition user);
bookPosition createNewBook(char* title, char* author, int year, int quantity);
userPosition createNewUserFile(char* username, char* password, int borrowed);
int addBookToDatabase(bookDBPosition uBookDB, char* title, char* author, int year, int quantity);
bookDBPosition createNewBookDB(char* title, char* author, int year, int quantity);
int updateBookDatabase(bookDBPosition uBookDB);
int readBooksFile(bookDBPosition uBookDB);
bookDBPosition createNewBookFile(char* title, char* author, int year, int quantityTotal, int quantityAvailible);
userPosition borrowNewBook(userPosition currentUser, bookDBPosition bookDatabase, userPosition uHead);
int updateUserBooks(userPosition currentUser);
int updateUsersFile(userPosition uHead);
int viewBorrowedBooks(userPosition currentUser);
int viewAllBooks(bookDBPosition uBookDB);
int search(bookDBPosition uBookDB, int searchInput, userPosition uHead);
int searchByTitle(bookDBPosition uBookDB, userPosition uHead);
int searchByAuthor(bookDBPosition uBookDB);
int searchByYear(bookDBPosition uBookDB);
int findUsers(char* title, userPosition uHead);
int viewAllUsers(userPosition uHead);
userPosition returnBook(userPosition currentUser, bookDBPosition bookDatabase, userPosition uHead);
bookDBPosition findBook(bookDBPosition uBookDB, char* title);
int removeBookFromUser(userPosition currentUser, char* title);
bookPosition findPrev(userPosition currentUser, char* title);
bookPosition findUserBook(userPosition currentUser, char* title);

int main()
{
    user uHead = { .username = {0}, .password = {0}, .borrowedBooks = 0, .bHead.title = {0}, .bHead.author = {0}, .bHead.year = 0, .bHead.quantity = 0, .bHead.next = NULL, .next = NULL };
    bookDB uBookDB = { .title = {0}, .author = {0}, .year = 0, .quantityTotal = 0, .quantityAvailible = 0, .next = NULL };
    userPosition currentUser = NULL;

    int input = 0;
    int searchInput = 0;
    int year = 0;
    int quantity = 0;
    char inputUsername[MAX_LENGTH] = "";
    char inputPassword[MAX_LENGTH] = "";
    char title[MAX_LENGTH] = "";
    char author[MAX_LENGTH] = "";

    //dodajemo podatke iz datoteke u liste
    readUsersFile(&uHead);
    readBooksFile(&uBookDB);

    while (1) {
        //slucaj da je korisnik logiran
        if (currentUser) {
            printf("\nWelcome, %s\n", currentUser->username);

            do {
                printf("(1) Borrow new book (2) Return borrowed book (3) View borrowed books (4) View all books (5) Search books (6) Logout\n");
                if (!scanf("%d%*c", &input) && input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6) {
                    printf(RED "Invalid input.\n" RESET);
                    fflush(stdin);
                }
            }while (input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6);

            switch (input) {
            case 1:
                currentUser = borrowNewBook(currentUser, &uBookDB, &uHead);
                break;
            case 2:
                currentUser = returnBook(currentUser, &uBookDB, &uHead);
                break;
            case 3:
                viewBorrowedBooks(currentUser);
                break;
            case 4:
                viewAllBooks(&uBookDB);
                break;
            case 5:
                printf("(1) Search by title (2) Search by author (3) Search by year\n");
                scanf("%d%*c", &searchInput);
                search(&uBookDB, searchInput, &uHead);
                break;
            case 6:
                currentUser = NULL;
                break;
            default:
                break;
            }
        }
        //slucaj da korisnik nije logiran
        else {
            do {
                printf("\n(1) Register (2) Login (3) Add book to database (4) View all books (5) Search books (6) View all users (7) Exit\n");
                if (!scanf("%d%*c", &input) && input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6 && input != 7) {
                    printf(RED "Invalid input.\n" RESET);
                    fflush(stdin);
                }
            } while (input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6 && input != 7);

            switch (input) {
            case 1:
                printf("Enter username: ");
                scanf("%[^\n]%*c", inputUsername);
                printf("Enter password: ");
                scanf("%[^\n]%*c", inputPassword);
                currentUser = userRegister(&uHead, inputUsername, inputPassword);
                break;
            case 2:
                printf("Enter username: ");
                scanf("%[^\n]%*c", inputUsername);
                printf("Enter password: ");
                scanf("%[^\n]%*c", inputPassword);
                currentUser = userLogin(&uHead, inputUsername, inputPassword);
                break;
            case 3:
                printf("Enter title: ");
                scanf("%[^\n]%*c", title);
                printf("Enter author: ");
                scanf("%[^\n]%*c", author);
                printf("Enter year: ");
                scanf("%d%*c", &year);
                printf("Enter quantity: ");
                scanf("%d%*c", &quantity);
                addBookToDatabase(&uBookDB, title, author, year, quantity);
                break;
            case 4:
                viewAllBooks(&uBookDB);
                break;
            case 5:
                printf("(1) Search by title (2) Search by author (3) Search by year\n");
                scanf("%d%*c", &searchInput);
                search(&uBookDB, searchInput, &uHead);
                break;
            case 6:
                viewAllUsers(&uHead);
                break;
            case 7:
                updateBookDatabase(&uBookDB);
                updateUsersFile(&uHead);
                return EXIT_SUCCESS;
            default:
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}

userPosition userRegister(userPosition uHead, char* username, char* password)
{
    FILE* filePointer = NULL;
    userPosition newUser = NULL;
    userPosition current = uHead;
    char buffer[MAX_BUFFER];
    char tempUsername[MAX_LENGTH];

    filePointer = fopen("users.txt", "r");
    if (!filePointer) {
        printf(RED "Failed to access users database.\n" RESET);
        return NULL;
    }

    //provjeravamo je li username vec zauzet
    while (!feof(filePointer)) {
        fscanf(filePointer, "%[^\n]%*c", buffer);
        sscanf(buffer, "%[^|]", tempUsername);

        if (strcmp(tempUsername, username) == 0) {
            printf(RED "Username already taken.\n" RESET);
            return NULL;
        }
    }

    fclose(filePointer);

    newUser = createNewUser(username, password);

    if (newUser) {
        while (current->next && strcmp(newUser->username, current->next->username) > 0) {
            current = current->next;
        }

        newUser->next = current->next;
        current->next = newUser;

        return newUser;
    }
    else {
        printf(RED "Registration failed.\n" RESET);
        return NULL;
    }
}

userPosition createNewUser(char* username, char* password)
{
    userPosition newUser = NULL;
    FILE* filePointer = NULL;
    char fileName[MAX_LENGTH] = "";

    filePointer = fopen("users.txt", "a");
    if (!filePointer) {
        printf(RED "Failed to access users database.\n" RESET);
        return NULL;
    }

    newUser = (userPosition)malloc(sizeof(user));

    if (newUser) {
        strcpy(newUser->username, username);
        strcpy(newUser->password, password);
        newUser->borrowedBooks = 0;
        strcpy(newUser->bHead.title, "");
        strcpy(newUser->bHead.author, "");
        newUser->bHead.year = 0;
        newUser->bHead.quantity = 0;
        newUser->bHead.next = NULL;
        newUser->next = NULL;

        fprintf(filePointer, "%s|%s|%d\n", newUser->username, newUser->password, newUser->borrowedBooks);
        fclose(filePointer);

        //stvaramo txt datoteku koja ce sadrzavati posudene knjige korisnika
        strcpy(fileName, newUser->username);
        strcat(fileName, ".txt");

        filePointer = fopen(fileName, "w");
        if (!filePointer) {
            printf(RED "Failed to create books file.\n" RESET);        
            return NULL;
        }
        fclose(filePointer);

        printf(GREEN "Registration successful.\n" RESET);

        return newUser;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

userPosition userLogin(userPosition uHead, char* username, char* password)
{
    userPosition current = uHead->next;

    while (current) {
        if (strcmp(current->username, username) == 0) {
            if (strcmp(current->password, password) == 0) {
                return current;
            }
            printf(RED "Wrong password.\n" RESET);
            return NULL;
        }
        current = current->next;
    }

    printf(RED "User not found.\n" RESET);
    return NULL;
}

int readUsersFile(userPosition uHead)
{
    userPosition newUser = NULL;
    userPosition current = uHead;
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    int borrowedBooks = 0;
    char buffer[MAX_BUFFER] = "";
    FILE* filePointer = NULL;

    filePointer = fopen("users.txt", "r");
    if (!filePointer) {
        printf(RED "Failed to access users database.\n" RESET);
        return EXIT_FAILURE;
    }

    while (!feof(filePointer)) {
        fscanf(filePointer, "%[^\n]\n", buffer);

        if (strcmp(buffer, "") != 0) {
            sscanf(buffer, "%[^|]%*c%[^|]%*c%d", username, password, &borrowedBooks);

            newUser = createNewUserFile(username, password, borrowedBooks);
            if (newUser) {
                while (current->next && strcmp(newUser->username, current->next->username) > 0) {
                    current = current->next;
                }
                newUser->next = current->next;
                current->next = newUser;
                addBooksToUser(newUser);
            }
            else {
                printf(RED "Failed to create new user from file.\n" RED);
                return EXIT_FAILURE;
            }
        }
    }

    fclose(filePointer);

    return EXIT_SUCCESS;
}

int addBooksToUser(userPosition user)
{
    FILE* filePointer = NULL;
    bookPosition newBook = NULL;
    char fileName[MAX_LENGTH] = "";
    char title[MAX_LENGTH] = "";
    char author[MAX_LENGTH] = "";
    char buffer[MAX_BUFFER] = "";
    int year = 0;
    int quantity = 0;

    strcpy(fileName, user->username);
    strcat(fileName, ".txt");

    filePointer = fopen(fileName, "r");
    if (!filePointer) {
        printf(RED"Failed to access borrowed books.\n" RESET);
        return EXIT_FAILURE;
    }

    while (!feof(filePointer)) {
        fscanf(filePointer, "%[^\n]\n", buffer);

        if (strcmp(buffer, "") != 0) {
            sscanf(buffer, "%[^|]%*c%[^|]%*c%d%*c%d", title, author, &year, &quantity); 
            newBook = createNewBook(title, author, year, quantity);
            newBook->next = user->bHead.next;
            user->bHead.next = newBook;
        }
    }

    fclose(filePointer);
    return EXIT_SUCCESS;
}

bookPosition createNewBook(char* title, char* author, int year, int quantity)
{
    bookPosition newBook = NULL;
    newBook = (bookPosition)malloc(sizeof(book));

    if (newBook) {
        strcpy(newBook->title, title);
        strcpy(newBook->author, author);
        newBook->year = year;
        newBook->quantity = quantity;
        newBook->next = NULL;

        return newBook;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

userPosition createNewUserFile(char* username, char* password, int borrowed)
{
    userPosition newUser = NULL;
    newUser = (userPosition)malloc(sizeof(user));

    if (newUser) {
        strcpy(newUser->username, username);
        strcpy(newUser->password, password);
        newUser->borrowedBooks = borrowed;
        newUser->next = NULL;
        strcpy(newUser->bHead.title, "");
        strcpy(newUser->bHead.author, "");
        newUser->bHead.year = 0;
        newUser->bHead.quantity = 0;
        newUser->bHead.next = NULL;

        return newUser;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

int addBookToDatabase(bookDBPosition uBookDB, char* title, char* author, int year, int quantity)
{
    FILE* filePointer = NULL;
    bookDBPosition newBookDB = NULL;
    bookDBPosition current = uBookDB->next;
    bookDBPosition curr = uBookDB;

    newBookDB = createNewBookDB(title, author, year, quantity);
    if (!newBookDB) {
        printf(RED "Failed to add new book to database.\n" RESET);
        return EXIT_FAILURE;
    }

    //provjeravamo postoji li vec knjiga u datoteci, ako postoji samo joj mijenjamo kvantitetu
    while (current) {
        if (strcmp(current->title, newBookDB->title) == 0 && strcmp(current->author, newBookDB->author) == 0 && current->year == newBookDB->year) {
            current->quantityTotal += quantity;
            current->quantityAvailible += quantity;
            free(newBookDB);
            updateBookDatabase(uBookDB);

            return EXIT_SUCCESS;
        }
        current = current->next;
    }

    filePointer = fopen("books.txt", "a");
    if (!filePointer) {
        printf(RED "Failed to access books database.\n" RESET);
        return EXIT_FAILURE;
    }

    while (curr->next && strcmp(newBookDB->title, curr->next->title) > 0) {
        curr = curr->next;
    }

    newBookDB->next = curr->next;
    curr->next = newBookDB;

    fprintf(filePointer, "%s|%s|%d|%d|%d\n", newBookDB->title, newBookDB->author, newBookDB->year, newBookDB->quantityTotal, newBookDB->quantityAvailible);
    fclose(filePointer);

    return EXIT_SUCCESS;
}

bookDBPosition createNewBookDB(char* title, char* author, int year, int quantity)
{
    bookDBPosition newBookDB = NULL;

    newBookDB = (bookDBPosition)malloc(sizeof(bookDB));
    if (newBookDB) {
        strcpy(newBookDB->title, title);
        strcpy(newBookDB->author, author);
        newBookDB->year = year;
        newBookDB->quantityTotal = quantity;
        newBookDB->quantityAvailible = quantity;
        newBookDB->next = NULL;

        return newBookDB;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

int updateBookDatabase(bookDBPosition uBookDB)
{
    bookDBPosition current = uBookDB->next;
    FILE* filePointer = NULL;

    filePointer = fopen("books.txt", "w");
    if (!filePointer) {
        printf(RED "Failed to open book database file.\n" RESET);
        return EXIT_FAILURE;
    }

    while (current) {
        fprintf(filePointer, "%s|%s|%d|%d|%d\n", current->title, current->author, current->year, current->quantityTotal, current->quantityAvailible);
        current = current->next;
    }

    fclose(filePointer);

    return EXIT_SUCCESS;
}

int readBooksFile(bookDBPosition uBookDB)
{
    bookDBPosition newBookDB = NULL;
    bookDBPosition current = uBookDB;
    FILE* filePointer = NULL;
    char buffer[MAX_BUFFER] = "";
    char title[MAX_LENGTH] = "";
    char author[MAX_LENGTH] = "";
    int year = 0;
    int quantityTotal = 0;
    int quantityAvailible = 0;

    filePointer = fopen("books.txt", "r");
    if (!filePointer) {
        printf(RED "Failed to open book database file.\n" RESET);
        return EXIT_FAILURE;
    }

    while(!feof(filePointer)){
        fscanf(filePointer, "%[^\n]\n", buffer);

        if (strcmp(buffer, "") != 0) {
            sscanf(buffer, "%[^|]%*c%[^|]%*c%d%*c%d%*c%d", title, author, &year, &quantityTotal, &quantityAvailible);

            newBookDB = createNewBookFile(title, author, year, quantityTotal, quantityAvailible);
            if (newBookDB) {
                while (current->next && strcmp(newBookDB->title, current->next->title) > 0) {
                    current = current->next;
                }

                newBookDB->next = current->next;
                current->next = newBookDB;
            }
            else {
                printf(RED "Failed to create new book from file.\n" RESET);
                fclose(filePointer);

                return EXIT_FAILURE;
            }
        }
    }

    fclose(filePointer);
    return EXIT_SUCCESS;
}

bookDBPosition createNewBookFile(char* title, char* author, int year, int quantityTotal, int quantityAvailible)
{
    bookDBPosition newBookDB = NULL;

    newBookDB = (bookDBPosition)malloc(sizeof(bookDB));
    if (newBookDB) {
        strcpy(newBookDB->title, title);
        strcpy(newBookDB->author, author);
        newBookDB->year = year;
        newBookDB->quantityTotal = quantityTotal;
        newBookDB->quantityAvailible = quantityAvailible;
        newBookDB->next = NULL;

        return newBookDB;
    }

    printf(RED "Failed to allocate memory.\n" RESET);
    return NULL;
}

userPosition borrowNewBook(userPosition currentUser, bookDBPosition bookDatabase, userPosition uHead)
{
    bookDBPosition selectedBook = NULL;
    bookDBPosition current = bookDatabase->next;
    bookPosition newBook = NULL;
    bookPosition curr = currentUser->bHead.next;
    char choice[MAX_LENGTH] = "";
    char title[MAX_LENGTH] = "";
    int quantity = 0;

    if (currentUser->borrowedBooks == 5) {
        printf(RED "You currently have 5 borrowed books!\n" RESET);
        return currentUser;
    }

    printf("Search book by title: ");
    scanf("%[^\n]%*c", title);
    printf("Choose quantity: ");
    scanf("%d%*c", &quantity);

    if (quantity <= 0) {
        printf(RED "Quantity has to be at least 1." RESET);
        return currentUser;
    }

    if (quantity > (5 - currentUser->borrowedBooks)) {
        printf(RED "You can borrow only 5 books at a time!.\n" RESET);
        printf("You are still allowed to borrow %d books.\n", 5 - currentUser->borrowedBooks);
        return currentUser;
    }

    while (current) {
        if (strcmp(title, current->title) == 0) {
            if (current->quantityAvailible >= quantity) {
                newBook = createNewBook(current->title, current->author, current->year, quantity);

                while (curr) {
                    //provjeravamo ima li korisnik vec primjeraka knjige koju posuduje
                    if (strcmp(curr->title, newBook->title) == 0 && strcmp(curr->author, newBook->author) == 0 && curr->year == newBook->year) {
                        curr->quantity += newBook->quantity;
                        current->quantityAvailible -= quantity;
                        currentUser->borrowedBooks += quantity;
                        updateUserBooks(currentUser);
                        updateBookDatabase(bookDatabase);
                        updateUsersFile(uHead);
                        free(newBook);

                        printf(GREEN "Successfully borrowed.\n" RESET);
                        return currentUser;
                    }
                    curr = curr->next;
                }

                newBook->next = currentUser->bHead.next;
                currentUser->bHead.next = newBook;

                current->quantityAvailible -= quantity;
                currentUser->borrowedBooks += quantity;

                updateUserBooks(currentUser);
                updateBookDatabase(bookDatabase);
                updateUsersFile(uHead);

                printf(GREEN "Successfully borrowed.\n" RESET);
                return currentUser;
            }
            else {
                printf("%s has %d copies availbile.\n", current->title, current->quantityAvailible);

                if (current->quantityAvailible > 0) {
                    printf("Do you want to borrow %d copies instead? (y/n)\n", current->quantityAvailible);
                    scanf("%[^\n]%*c", choice);

                    if (strcmp(choice, "y") == 0) {
                        newBook = createNewBook(current->title, current->author, current->year, current->quantityAvailible);

                        while (curr) {
                            if (strcmp(curr->title, newBook->title) == 0 && strcmp(curr->author, newBook->author) == 0 && curr->year == newBook->year) {
                                curr->quantity += current->quantityAvailible;
                                current->quantityAvailible = 0;
                                currentUser->borrowedBooks += current->quantityAvailible;
                                updateUserBooks(currentUser);
                                updateBookDatabase(bookDatabase);
                                updateUsersFile(uHead);
                                free(newBook);

                                printf(GREEN "Successfully borrowed.\n" RESET);
                                return currentUser;
                            }
                            curr = curr->next;
                        }

                        newBook->next = currentUser->bHead.next;
                        currentUser->bHead.next = newBook;

                        current->quantityAvailible = 0;
                        currentUser->borrowedBooks += current->quantityAvailible;

                        updateUserBooks(currentUser);
                        updateBookDatabase(bookDatabase);
                        updateUsersFile(uHead);

                        printf(GREEN "Successfully borrowed.\n" RESET);
                        return currentUser;
                    }
                    return currentUser;
                }
                return currentUser;
            }
        }
        current = current->next;
    }

    printf("%s does not exist in library.\n", title);
    return currentUser;   
}

int updateUserBooks(userPosition currentUser)
{
    FILE* filePointer = NULL;
    bookPosition current = currentUser->bHead.next;
    char fileName[MAX_LENGTH] = "";

    strcpy(fileName, currentUser->username);
    strcat(fileName, ".txt");

    filePointer = fopen(fileName, "w");
    if (!filePointer) {
        printf(RED "Failed to open book list for current user.\n" RESET);
        return EXIT_FAILURE;
    }

    while (current) {
        fprintf(filePointer, "%s|%s|%d|%d\n", current->title, current->author, current->year, current->quantity);
        current = current->next;
    }

    fclose(filePointer);
    return EXIT_SUCCESS;
}

int updateUsersFile(userPosition uHead)
{
    userPosition current = uHead->next;
    FILE* filePointer = NULL;

    filePointer = fopen("users.txt", "w");
    if (!filePointer) {
        printf(RED "Failed to access users database.\n" RESET);
        return EXIT_FAILURE;
    }

    while (current) {
        fprintf(filePointer, "%s|%s|%d\n", current->username, current->password, current->borrowedBooks);
        current = current->next;
    }

    fclose(filePointer);
    return EXIT_SUCCESS;
}

int viewBorrowedBooks(userPosition currentUser)
{
    bookPosition current = NULL;

    if (currentUser->borrowedBooks == 0) {
        printf("You have no borrowed books to display.\n");
        return EXIT_SUCCESS;
    }

    printf("\nTITLE\t\t\t  AUTHOR     \t  YEAR\t     QUANTITY\n");

    current = currentUser->bHead.next;
    while (current) {
        printf("%-25s %-15s %-10d %-10d\n", current->title, current->author, current->year, current->quantity);
        current = current->next;
    }  
    printf("\n");

    return EXIT_SUCCESS;
}

int viewAllBooks(bookDBPosition uBookDB)
{
    bookDBPosition current = uBookDB->next;

    if (current == NULL) {
        printf("No books availible.\n");
        return EXIT_SUCCESS;
    }

    printf("\nTITLE\t\t\t  AUTHOR     \t  YEAR\t     TOTAL\tAVAILIBLE\n");

    while (current) {
        printf("%-25s %-15s %-10d %-10d %-10d\n", current->title, current->author, current->year, current->quantityTotal, current->quantityAvailible);
        current = current->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int search(bookDBPosition uBookDB, int searchInput, userPosition uHead)
{
    if (searchInput != 1 && searchInput != 2 && searchInput != 3) {
        printf(RED "Invalid input!\n" RESET);
        return EXIT_FAILURE;
    }

    switch (searchInput) {
    case 1:
        searchByTitle(uBookDB, uHead);
        break;
    case 2:
        searchByAuthor(uBookDB);
        break;
    case 3:
        searchByYear(uBookDB);
        break;
    default:
        break;
    }

    return EXIT_SUCCESS;
}

int searchByTitle(bookDBPosition uBookDB, userPosition uHead)
{
    bookDBPosition current = uBookDB->next;
    userPosition currentUser = uHead->next;
    bookPosition currentBook = NULL;
    int count = 0;
    char input[MAX_LENGTH] = "";

    if (!current) {
        printf("No books availible.\n");
        return EXIT_SUCCESS;
    }

    printf("Enter title: ");
    scanf("%[^\n]%*c", input);

    while (current) {
        if (strcmp(input, current->title) == 0) {
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("%s does not exist in library.\n", input);
        return EXIT_SUCCESS;
    }

    printf("\nTITLE\t\t\t  AUTHOR     \t  YEAR\t     TOTAL\tAVAILIBLE\n");

    current = uBookDB->next;
    while (current) {
        if (strcmp(input, current->title) == 0) {
            printf("%-25s %-15s %-10d %-10d %-10d\n", current->title, current->author, current->year, current->quantityTotal, current->quantityAvailible);
        }
        current = current->next;
    }
    printf("\n");

    count = findUsers(input, uHead);

    if (count == 0) {
        printf("No users borrowing this book currently.\n");
        return EXIT_SUCCESS;
    }

    printf("Users borrowing this book currently:\n");

    while (currentUser) {
        currentBook = currentUser->bHead.next;

        while (currentBook) {
            if (strcmp(currentBook->title, input) == 0) {
                printf("%s, %d\n", currentUser->username, currentBook->quantity);
            }
            currentBook = currentBook->next;
        }
        currentUser = currentUser->next;
    } 
    printf("\n");

    return EXIT_SUCCESS;
}

int searchByAuthor(bookDBPosition uBookDB)
{
    bookDBPosition current = uBookDB->next;
    int count = 0;
    char input[MAX_LENGTH] = "";

    if (!current) {
        printf("No books availible.\n");
        return EXIT_SUCCESS;
    }

    printf("Enter author: ");
    scanf("%[^\n]%*c", input);

    while (current) {
        if (strcmp(input, current->author) == 0) {
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("%s has no books in library.\n", input);
        return EXIT_SUCCESS;
    }

    printf("\nTITLE\t\t\t  AUTHOR     \t  YEAR\t     TOTAL\tAVAILIBLE\n");

    current = uBookDB->next;
    while (current) {
        if (strcmp(input, current->author) == 0) {
            printf("%-25s %-15s %-10d %-10d %-10d\n", current->title, current->author, current->year, current->quantityTotal, current->quantityAvailible);
        }
        current = current->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int searchByYear(bookDBPosition uBookDB)
{
    bookDBPosition current = uBookDB->next;
    int count = 0;
    int input = 0;

    if (!current) {
        printf("No books availible.\n");
        return EXIT_SUCCESS;
    }

    printf("Enter year: ");
    scanf("%d", &input);

    while (current) {
        if (input == current->year) {
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("No books from %d. exits in library.\n", input);
        return EXIT_SUCCESS;
    }

    printf("\nTITLE\t\t\t  AUTHOR     \t  YEAR\t     TOTAL\tAVAILIBLE\n");

    current = uBookDB->next;
    while (current) {
        if (input == current->year) {
            printf("%-25s %-15s %-10d %-10d %-10d\n", current->title, current->author, current->year, current->quantityTotal, current->quantityAvailible);
        }
        current = current->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int findUsers(char* title, userPosition uHead)
{
    userPosition currentUser = uHead->next;
    bookPosition currentBook = NULL;
    int count = 0;

    while (currentUser) {
        currentBook = currentUser->bHead.next;

        while (currentBook) {
            if (strcmp(currentBook->title, title) == 0) {
                count++;
            }
            currentBook = currentBook->next;
        }
        currentUser = currentUser->next;
    }
    
    return count;
}

int viewAllUsers(userPosition uHead)
{
    userPosition currentUser = uHead->next;
    bookPosition currentBook = NULL;

    if (!currentUser) {
        printf("No users availible.\n");
        return EXIT_SUCCESS;
    }

    while (currentUser) {
        printf("Username: %s\n", currentUser->username);

        if (currentUser->borrowedBooks == 0) {
            printf("No borrowed books.\n\n");
        }
        else {
            printf("TITLE\t\t\t  AUTHOR     \t  YEAR\t     QUANTITY\n");

            currentBook = currentUser->bHead.next;
            while (currentBook) {
                printf("%-25s %-15s %-10d %-10d\n", currentBook->title, currentBook->author, currentBook->year, currentBook->quantity);
                currentBook = currentBook->next;
            }
            printf("\n");
        }
        currentUser = currentUser->next;
    }

    return EXIT_SUCCESS;
}

userPosition returnBook(userPosition currentUser, bookDBPosition bookDatabase, userPosition uHead)
{
    bookPosition currentBook = currentUser->bHead.next;
    bookDBPosition returnedBook = NULL;
    bookPosition userBook = NULL;
    char title[MAX_LENGTH] = "";
    char choice[MAX_LENGTH] = "";
    int quantity = 0;

    if (currentUser->borrowedBooks == 0) {
        printf("You don't have any borrowed books.\n");
        return currentUser;
    }

    printf("Your books:\n");
    viewBorrowedBooks(currentUser);

    printf("Enter title: ");
    scanf("%[^\n]%*c", title);

    while (currentBook) {
        if (strcmp(currentBook->title, title) == 0) {
            printf("Enter quantity: ");
            scanf("%d%*c", &quantity);

            if (quantity <= 0) {
                printf(RED "Quantity has to be at least 1." RESET);
                return currentUser;
            }

            if (quantity > currentBook->quantity) {
                printf("You have %d copies of %s, do you want to return all? (y/n): ", currentBook->quantity, currentBook->title);
                scanf("%[^\n]%*c", choice);

                if (strcmp(choice, "y") == 0) {
                    currentUser->borrowedBooks -= currentBook->quantity;

                    returnedBook = findBook(bookDatabase, title);
                    if (returnedBook) {
                        returnedBook->quantityAvailible += currentBook->quantity;
                    }

                    removeBookFromUser(currentUser, title);

                    updateBookDatabase(bookDatabase);
                    updateUsersFile(uHead);
                    updateUserBooks(currentUser);

                    printf(GREEN "Book successfully returned.\n" RESET);
                    return currentUser;
                }
                else {
                    return currentUser;
                }
            }
            else if (quantity < currentBook->quantity) {
                currentUser->borrowedBooks -= quantity;

                returnedBook = findBook(bookDatabase, title);
                if (returnedBook) {
                    returnedBook->quantityAvailible += quantity;
                }

                userBook = findUserBook(currentUser, title);
                if (userBook) {
                    userBook->quantity -= quantity;
                }

                updateBookDatabase(bookDatabase);
                updateUsersFile(uHead);
                updateUserBooks(currentUser);

                printf(GREEN "Book successfully returned.\n" RESET);
                return currentUser;
            }
            else {
                currentUser->borrowedBooks -= quantity;

                returnedBook = findBook(bookDatabase, title);
                if (returnedBook) {
                    returnedBook->quantityAvailible += quantity;
                }

                removeBookFromUser(currentUser, title);

                updateBookDatabase(bookDatabase);
                updateUsersFile(uHead);
                updateUserBooks(currentUser);

                printf(GREEN "Book successfully returned.\n" RESET);
                return currentUser;
            }
        }
        currentBook = currentBook->next;
    }

    printf("Book %s not found.\n", title); 
    return currentUser;
}

bookDBPosition findBook(bookDBPosition bookDatabase, char* title)
{
    bookDBPosition current = bookDatabase->next;

    while (current) {
        if (strcmp(current->title, title) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int removeBookFromUser(userPosition currentUser, char* title)
{
    bookPosition currentBook = currentUser->bHead.next;
    bookPosition prev = NULL;

    while (currentBook) {
        if (strcmp(currentBook->title, title) == 0) {
            prev = findPrev(currentUser, title);
            prev->next = currentBook->next;
            free(currentBook);

            return EXIT_SUCCESS;
        }
        currentBook = currentBook->next;
    }

    return EXIT_FAILURE;
}

bookPosition findPrev(userPosition currentUser, char* title)
{
    bookPosition current = &(currentUser->bHead);

    while (current->next) {
        if (strcmp(current->next->title, title) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

bookPosition findUserBook(userPosition currentUser, char* title)
{
    bookPosition current = currentUser->bHead.next;

    while (current) {
        if (strcmp(current->title, title) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}