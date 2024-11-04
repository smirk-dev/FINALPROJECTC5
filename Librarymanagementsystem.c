#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Book 
{
    char title[100];
    char author[50];
    int id;
    int available;
};
void addBook() 
{
    FILE *fptr = fopen("library.txt", "ab");
    if (fptr == NULL) 
    {
        printf("Error opening file!\n");
        return;
    }
    struct Book book;
    printf("Enter Book Title: ");
    scanf(" %[^\n]s", book.title);
    printf("Enter Author Name: ");
    scanf(" %[^\n]s", book.author);
    printf("Enter Book ID: ");
    scanf("%d", &book.id);
    book.available = 1;
    fwrite(&book, sizeof(book), 1, fptr);
    fclose(fptr);
    printf("Book added successfully!\n");
}
void displayBooks() 
{
    FILE *fptr = fopen("library.txt", "rb");
    if (fptr == NULL) 
    {
        printf("No books found.\n");
        return;
    }
    struct Book book;
    printf("\n-----Library Books-----\n");
    while (fread(&book, sizeof(book), 1, fptr)) 
    {
        printf("Title: %s | Author: %s | Book ID: %d | Available: %s\n", book.title, book.author, book.id, book.available ? "Yes" : "No");
    }
    fclose(fptr);
}
void issueBook() 
{
    int bookID;
    printf("Enter Book ID to issue: ");
    scanf("%d", &bookID);
    FILE *fptr = fopen("library.txt", "rb+");
    if (fptr == NULL) {
        printf("No books found.\n");
        return;
    }
    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(book), 1, fptr)) 
    {
        if (book.id == bookID) 
        {
            if (book.available == 1) 
            {
                book.available = 0;
                fseek(fptr, -sizeof(book), SEEK_CUR);
                fwrite(&book, sizeof(book), 1, fptr);
                printf("Book issued successfully!\n");
            } else 
            {
                printf("Book is already issued.\n");
            }
            found = 1;
            break;
        }
    }
    fclose(fptr);
    if (!found) 
    {
        printf("Book not found.\n");
    }
}
void returnBook() 
{
    int bookID;
    printf("Enter Book ID to return: ");
    scanf("%d", &bookID);
    FILE *fptr = fopen("library.txt", "rb+");
    if (fptr == NULL) 
    {
        printf("No books found.\n");
        return;
    }
    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(book), 1, fptr)) 
    {
        if (book.id == bookID) 
        {
            if (book.available == 0) 
            {
                book.available = 1;
                fseek(fptr, -sizeof(book), SEEK_CUR);
                fwrite(&book, sizeof(book), 1, fptr);
                printf("Book returned successfully!\n");
            } else 
            {
                printf("Book was not issued.\n");
            }
            found = 1;
            break;
        }
    }
    fclose(fptr);
    if (!found) {
        printf("Book not found.\n");
    }
}
int main() 
{
    int choice;
    do 
    {
        printf("\n---Library Management System---\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                issueBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);
    return 0;
}