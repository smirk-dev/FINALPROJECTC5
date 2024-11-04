#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if (fptr == NULL) {
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
    if (fptr == NULL) {
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
    if (fptr == NULL) {
        printf("No accounts found.\n");
        return;
    }
    struct Account acc;
    int found = 0;
    while (fread(&acc, sizeof(acc), 1, fptr)) 
    {
        if (acc.accNo == accNo) {
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
int main() 
{
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
    return 0;
}