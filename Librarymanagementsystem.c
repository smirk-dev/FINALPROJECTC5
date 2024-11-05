// Library Management System
#include <stdio.h>
#include <string.h>

void libraryManagementSystem() {
    struct Book {
        char title[100];
        char author[50];
        int id;
        int available;
        char borrower[50];
        char dueDate[11];  // Format: YYYY-MM-DD
    };

    void addBook() {
        FILE *fp = fopen("library.dat", "ab");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return;
        }
        
        struct Book book;
        printf("\nEnter Book Details\n");
        printf("=================\n");
        
        printf("Enter Title: ");
        getchar();
        fgets(book.title, sizeof(book.title), stdin);
        book.title[strcspn(book.title, "\n")] = 0;
        
        printf("Enter Author: ");
        fgets(book.author, sizeof(book.author), stdin);
        book.author[strcspn(book.author, "\n")] = 0;
        
        printf("Enter Book ID: ");
        scanf("%d", &book.id);
        
        book.available = 1;
        strcpy(book.borrower, "None");
        strcpy(book.dueDate, "N/A");
        
        fwrite(&book, sizeof(struct Book), 1, fp);
        fclose(fp);
        printf("\nBook added successfully!\n");
    }

    void displayBooks() {
        FILE *fp = fopen("library.dat", "rb");
        if (fp == NULL) {
            printf("No books in library.\n");
            return;
        }
        struct Book book;
        printf("\nLibrary Inventory\n");
        printf("================\n");
        printf("%-5s %-30s %-20s %-10s %-20s %-12s\n", 
               "ID", "Title", "Author", "Status", "Borrower", "Due Date");
        printf("------------------------------------------------------------------------------\n");
        while (fread(&book, sizeof(struct Book), 1, fp)) {
            printf("%-5d %-30s %-20s %-10s %-20s %-12s\n",
                   book.id,
                   book.title,
                   book.author,
                   book.available ? "Available" : "Borrowed",
                   book.borrower,
                   book.dueDate);
        }
        fclose(fp);
    }

    void searchBook() {
        FILE *fp = fopen("library.dat", "rb");
        if (fp == NULL) {
            printf("No books in library.\n");
            return;
        }
        
        int searchId;
        printf("Enter Book ID to search: ");
        scanf("%d", &searchId);
        
        struct Book book;
        int found = 0;
        
        while (fread(&book, sizeof(struct Book), 1, fp)) {
            if (book.id == searchId) {
                printf("\nBook Found!\n");
                printf("==========\n");
                printf("Title: %s\n", book.title);
                printf("Author: %s\n", book.author);
                printf("Status: %s\n", book.available ? "Available" : "Borrowed");
                printf("Borrower: %s\n", book.borrower);
                printf("Due Date: %s\n", book.dueDate);
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Book not found!\n");
        }
        fclose(fp);
    }

    void issueBook() {
        FILE *fp = fopen("library.dat", "rb+");
        if (fp == NULL) {
            printf("No books in library.\n");
            return;
        }
        
        int searchId;
        printf("Enter Book ID to issue: ");
        scanf("%d", &searchId);
        
        struct Book book;
        int found = 0;
        
        while (fread(&book, sizeof(struct Book), 1, fp)) {
            if (book.id == searchId) {
                if (book.available) {
                    book.available = 0;
                    
                    printf("Enter Borrower Name: ");
                    getchar();
                    fgets(book.borrower, sizeof(book.borrower), stdin);
                    book.borrower[strcspn(book.borrower, "\n")] = 0;
                    
                    printf("Enter Due Date (YYYY-MM-DD): ");
                    fgets(book.dueDate, sizeof(book.dueDate), stdin);
                    book.dueDate[strcspn(book.dueDate, "\n")] = 0;
                    
                    fseek(fp, -sizeof(struct Book), SEEK_CUR);
                    fwrite(&book, sizeof(struct Book), 1, fp);
                    printf("Book issued successfully!\n");
                } else {
                    printf("Book is already borrowed by: %s\n", book.borrower);
                    printf("Due Date: %s\n", book.dueDate);
                }
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Book not found!\n");
        }
        fclose(fp);
    }

    void returnBook() {
        FILE *fp = fopen("library.dat", "rb+");
        if (fp == NULL) {
            printf("No books in library.\n");
            return;
        }
        
        int searchId;
        printf("Enter Book ID to return: ");
        scanf("%d", &searchId);
        
        struct Book book;
        int found = 0;
        
        while (fread(&book, sizeof(struct Book), 1, fp)) {
            if (book.id == searchId) {
                if (!book.available) {
                    book.available = 1;
                    strcpy(book.borrower, "None");
                    strcpy(book.dueDate, "N/A");
                    
                    fseek(fp, -sizeof(struct Book), SEEK_CUR);
                    fwrite(&book, sizeof(struct Book), 1, fp);
                    printf("Book returned successfully!\n");
                } else {
                    printf("Book is already in library!\n");
                }
                found = 1;
                break;
            }
        }
        
        if (!found) {
            printf("Book not found!\n");
        }
        fclose(fp);
    }

    void removeBook() {
        FILE *fp = fopen("library.dat", "rb");
        FILE *tempFp = fopen("temp.dat", "wb");
        
        if (fp == NULL) {
            printf("No books in library.\n");
            return;
        }
        
        int searchId;
        printf("Enter Book ID to remove: ");
        scanf("%d", &searchId);
        
        struct Book book;
        int found = 0;
        
        while (fread(&book, sizeof(struct Book), 1, fp)) {
            if (book.id == searchId) {
                found = 1;
                printf("Book '%s' removed from library.\n", book.title);
                continue;
            }
            fwrite(&book, sizeof(struct Book), 1, tempFp);
        }
        
        if (!found) {
            printf("Book not found!\n");
        }
        
        fclose(fp);
        fclose(tempFp);
        
        remove("library.dat");
        rename("temp.dat", "library.dat");
    }
    
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("=======================\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Issue Book\n");
        printf("5. Return Book\n");
        printf("6. Remove Book\n");
        printf("7. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchBook();
                break;
            case 4:
                issueBook();
                break;
            case 5:
                returnBook();
                break;
            case 6:
                removeBook();
                break;
            case 7:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);
}

int main() {
    libraryManagementSystem();
    return 0;
}
