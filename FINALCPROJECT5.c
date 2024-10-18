#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void bankManagementSystem();
void libraryManagementSystem();
void quizGame();
void snakeAndLadderGame();
void typingSpeedTest();
int main() 
{
    int choice;
    do 
    {
        printf("\n--- Project Selector ---\n");
        printf("1. Bank Management System\n");
        printf("2. Library Management System\n");
        printf("3. Quiz Game\n");
        printf("4. Snake and Ladder Game\n");
        printf("5. Typing Speed Test\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) 
        {
            case 1:
                bankManagementSystem();
                break;
            case 2:
                libraryManagementSystem();
                break;
            case 3:
                quizGame();
                break;
            case 4:
                snakeAndLadderGame();
                break;
            case 5:
                typingSpeedTest();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } 
    while (choice != 6);
    
    return 0;
}
// Bank Management System
void bankManagementSystem() 
{
    struct Account {
        char name[50];
        int accNo;
        float balance;
    };
    void createAccount() 
    {
        FILE *fptr = fopen("accounts.txt", "ab");
        if (fptr == NULL) 
        {
            printf("Error opening file!\n");
            return;
        }
        struct Account acc;
        printf("Enter Name: ");
        scanf("%s", acc.name);
        printf("Enter Account Number: ");
        scanf("%d", &acc.accNo);
        acc.balance = 0.0;
        fwrite(&acc, sizeof(acc), 1, fptr);
        fclose(fptr);
        printf("Account created successfully!\n");
    }
    void displayAccounts() 
    {
        FILE *fptr = fopen("accounts.txt", "rb");
        if (fptr == NULL) 
        {
            printf("No accounts found.\n");
            return;
        }
        struct Account acc;
        printf("\n-----Account Information-----\n");
        while (fread(&acc, sizeof(acc), 1, fptr)) 
        {
            printf("Name: %s | Account No: %d | Balance: %.2f\n", acc.name, acc.accNo, acc.balance);
        }
        fclose(fptr);
    }
    void depositMoney() 
    {
        int accNo;
        float depositAmount;
        printf("Enter Account Number to deposit: ");
        scanf("%d", &accNo);
        printf("Enter amount to deposit: ");
        scanf("%f", &depositAmount);
        FILE *fptr = fopen("accounts.txt", "rb+");
        if (fptr == NULL) 
        {
            printf("No accounts found.\n");
            return;
        }
        struct Account acc;
        int found = 0;
        while (fread(&acc, sizeof(acc), 1, fptr)) 
        {
            if (acc.accNo == accNo) 
            {
                acc.balance += depositAmount;
                fseek(fptr, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fptr);
                found = 1;
                break;
            }
        }
        fclose(fptr);
        if (found) 
        {
            printf("Deposit successful!\n");
        } else 
        {
            printf("Account not found.\n");
        }
    }
    void withdrawMoney() 
    {
        int accNo;
        float withdrawAmount;
        printf("Enter Account Number to withdraw: ");
        scanf("%d", &accNo);
        printf("Enter amount to withdraw: ");
        scanf("%f", &withdrawAmount);
        FILE *fptr = fopen("accounts.txt", "rb+");
        if (fptr == NULL) 
        {
            printf("No accounts found.\n");
            return;
        }
        struct Account acc;
        int found = 0;
        while (fread(&acc, sizeof(acc), 1, fptr)) 
        {
            if (acc.accNo == accNo) 
            {
                if (withdrawAmount > acc.balance) 
                {
                    printf("Insufficient balance!\n");
                } else 
                {
                    acc.balance -= withdrawAmount;
                    fseek(fptr, -sizeof(acc), SEEK_CUR);
                    fwrite(&acc, sizeof(acc), 1, fptr);
                    printf("Withdrawal successful!\n");
                }
                found = 1;
                break;
            }
        }
        fclose(fptr);
        if (!found) 
        {
            printf("Account not found.\n");
        }
    }
    int choice;
    do 
    {
        printf("\n---Bank Management System---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Display Accounts\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) 
        {
            case 1:
                createAccount();
                break;
            case 2:
                depositMoney();
                break;
            case 3:
                withdrawMoney();
                break;
            case 4:
                displayAccounts();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);
}
// Library Management System
void libraryManagementSystem() 
{
    struct Book {
        char title[100];
        char author[50];
        int id;
        int available;
    };
    void addBook() 
    {
        FILE *fptr = fopen("library.txt", "ab");
        if (fptr == NULL) {
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
                if (book.available == 1) 
                {
                    book.available = 0;
                    fseek(fptr, -sizeof(book), SEEK_CUR);
                    fwrite(&book, sizeof(book), 1, fptr);
                    printf("Book issued successfully!\n");
                } 
                else 
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
            if (book.id == bookID) {
                if (book.available == 0) 
                {
                    book.available = 1;
                    fseek(fptr, -sizeof(book), SEEK_CUR);
                    fwrite(&book, sizeof(book), 1, fptr);
                    printf("Book returned successfully!\n");
                } 
                else 
                {
                    printf("Book was not issued.\n");
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
}
// Quiz Game
void quizGame() 
{
    struct Question 
    {
        char question[256];
        char options[4][50];
        char correctOption;
    };
    int askQuestion(struct Question q) 
    {
        printf("%s\n", q.question);
        for (int i = 0; i < 4; i++) {
            printf("%c. %s\n", 'A' + i, q.options[i]);
        }
        char answer;
        printf("Enter your answer (A, B, C, D): ");
        scanf(" %c", &answer);
        if (answer == q.correctOption) 
        {
            printf("Correct!\n\n");
            return 1;
        } else {
            printf("Wrong! Correct answer is %c\n\n", q.correctOption);
            return 0;
        }
    }
    void startQuiz() {
        struct Question questions[5] = 
        {
            {"Which country has the highest life expectancy?", {"Paris", "Hong Kong", "Rome", "Berlin"}, 'B'},
            {"What is the most common surname in the United States?", {"Shakespeare", "Dickens", "Smith", "Tolkien"}, 'C'},
            {"What is the chemical symbol for water?", {"CO2", "H2O", "NaCl", "O2"}, 'B'},
            {"Which planet is known as the Red Planet?", {"Earth", "Mars", "Jupiter", "Saturn"}, 'B'},
            {"Who painted the Mona Lisa?", {"Van Gogh", "Picasso", "Da Vinci", "Monet"}, 'C'}
        };
        int score = 0;
        printf("Welcome to the Quiz!\n");
        printf("---------------------\n");
        for (int i = 0; i < 5; i++) {
            score += askQuestion(questions[i]);
        }
        printf("You completed the quiz!\n");
        printf("Your final score is: %d/5\n", score);
    }
    startQuiz();
}
// Snake and Ladder Game
void snakeAndLadderGame() 
{
    int rollDie() { return rand() % 6 + 1; }
    int player1 = 0, player2 = 0;
    void printBoard() 
    {
        int board[101];
        for (int i = 1; i <= 100; i++) 
        {
            board[i] = i;
        }
        int alt = 0;
        int iterLR = 101;
        int iterRL = 80;
        int val = 100;
        while (val--) 
        {
            if (alt == 0) 
            {
                iterLR--;
                if (iterLR == player1) 
                {
                    printf("#P1 ");
                } 
                else if (iterLR == player2) 
                {
                    printf("#P2 ");
                } 
                else
                    printf("%d ", board[iterLR]);

                if (iterLR % 10 == 1) 
                {
                    printf("\n\n");
                    alt = 1;
                    iterLR -= 10;
                }
            } 
            else 
            {
                iterRL++;
                if (iterRL == player1) 
                {
                    printf("#P1 ");
                } 
                else if (iterRL == player2) 
                {
                    printf("#P2 ");
                } 
                else
                    printf("%d ", board[iterRL]);

                if (iterRL % 10 == 0) 
                {
                    printf("\n\n");
                    alt = 0;
                    iterRL -= 30;
                }
            }
            if (iterRL == 10)
                break;
        }
        printf("\n");
    }
    int movePlayer(int currentPlayer, int roll) 
    {
        int newPosition = currentPlayer + roll;
        int snakesAndLadders[101];
        for (int i = 0; i <= 100; i++) 
        {
            snakesAndLadders[i] = 0;
        }
        snakesAndLadders[6] = 40;
        snakesAndLadders[23] = -10;
        snakesAndLadders[45] = -7;
        snakesAndLadders[61] = -18;
        snakesAndLadders[65] = -8;
        snakesAndLadders[77] = 5;
        snakesAndLadders[98] = -10;
        int newSquare = newPosition + snakesAndLadders[newPosition];
        if (newSquare > 100) 
        {
            return currentPlayer;
        }
        return newSquare;
    }
    srand(time(0));
    int currentPlayer = 1;
    int won = 0;
    printf("Snake and Ladder Game\n");
    while (!won) 
    {
        printf("\nPlayer %d, press Enter to roll the die...", currentPlayer);
        getchar();
        int roll = rollDie();
        printf("You rolled a %d.\n", roll);
        if (currentPlayer == 1) 
        {
            player1 = movePlayer(player1, roll);
            printf("Player 1 is now at square %d.\n\n", player1);
            printBoard();
            if (player1 == 100) 
            {
                printf("Player 1 wins!\n");
                won = 1;
            }
        } 
        else 
        {
            player2 = movePlayer(player2, roll);
            printf("Player 2 is now at square %d.\n\n", player2);
            printBoard();
            if (player2 == 100) 
            {
                printf("Player 2 wins!\n");
                won = 1;
            }
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}
// Typing Speed Test
void typingSpeedTest() 
{
    char sentence[] = "The quick brown fox jumps over the lazy dog.";
    char input[100];
    clock_t start, end;
    printf("Type the following sentence:\n");
    printf("\"%s\"\n\n", sentence);
    printf("Press Enter to start...\n");
    getchar();
    start = clock();
    printf("Start typing:\n");
    fgets(input, sizeof(input), stdin);
    end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    int word_count = 0;
    char *token = strtok(input, " ");
    while (token != NULL) 
    {
        word_count++;
        token = strtok(NULL, " ");
    }
    double wpm = (word_count / time_taken) * 60;
    printf("\nTime taken: %.2f seconds\n", time_taken);
    printf("You typed %d words.\n", word_count);
    printf("Your typing speed is: %.2f WPM\n", wpm);
}