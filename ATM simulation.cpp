#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "atm_users.txt"

struct Account {
    char name[50];
    int pin;
    float balance;
};


void createAccount();
int login(struct Account *user);
void displayMenu(struct Account *user);
void checkBalance(struct Account *user);
void depositMoney(struct Account *user);
void withdrawMoney(struct Account *user);
void updateAccount(struct Account user);

int main() {
    int choice;
    struct Account user;

    while (1) {
        printf("\n===== ATM SIMULATION SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                if (login(&user)) {
                    printf("\nWelcome, %s!\n", user.name);
                    displayMenu(&user);
                } else {
                    printf("Login failed. Please try again.\n");
                }
                break;
            case 3:
                printf("Thank you for using our ATM. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}


void createAccount() 
{
    struct Account newUser;
    FILE *fp;

    printf("\n--- Create New Account ---\n");
    printf("Enter your name: ");
    scanf("%s", newUser.name);
    printf("Set a 4-digit PIN: ");
    scanf("%d", &newUser.pin);
    newUser.balance = 0.0;

    fp = fopen(FILE_NAME, "a");
    if (fp == NULL) 
	{
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%s %d %.2f\n", newUser.name, newUser.pin, newUser.balance);
    fclose(fp);

    printf("Account created successfully!\n");
}


int login(struct Account *user) 
{
    char name[50];
    int pin;
    FILE *fp;

    printf("\n--- Login ---\n");
    printf("Enter Username: ");
    scanf("%s", &name);
    printf("Enter PIN: ");
    scanf("%d", &pin);

    fp = fopen(FILE_NAME, "r");
    if (fp == NULL) 
	{
        printf("No accounts found. Please create one first.\n");
        return 0;
    }

    while (fscanf(fp, "%s %d %f", user->name, &user->pin, &user->balance) != EOF) 
	{
        if (strcmp(user->name, name) == 0 && user->pin == pin) 
		{
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}


void displayMenu(struct Account *user) 
{
    int choice;
    do {
        printf("\n----- ATM MENU -----\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(user);
                break;
            case 2:
                depositMoney(user);
                break;
            case 3:
                withdrawMoney(user);
                break;
            case 4:
                updateAccount(*user);
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);
}


void checkBalance(struct Account *user) 
{
    printf("\nCurrent Balance: Rs.%.2f\n", user->balance);
}


void depositMoney(struct Account *user) 
{
    float amount;
    printf("Enter amount to deposit: Rs.");
    scanf("%f", &amount);

    if (amount > 0) 
	{
        user->balance += amount;
        printf("Rs.%.2f deposited successfully!\n", amount);
        printf("Updated balance: Rs.%.2f\n", user->balance);
    } 
	else 
	{
        printf("Invalid amount!\n");
    }
}


void withdrawMoney(struct Account *user) {
    float amount;
    printf("Enter amount to withdraw: Rs.");
    scanf("%f", &amount);

    if (amount <= 0) 
	{
        printf("Invalid amount!\n");
    } 
	else if (amount > user->balance) 
	{
        printf("Insufficient balance!\n");
    } 
	else 
	{
        user->balance -= amount;
        printf("?%.2f withdrawn successfully!\n", amount);
        printf("Remaining balance: Rs.%.2f\n", user->balance);
    }
}


void updateAccount(struct Account user) 
{
    struct Account temp;
    FILE *fp, *tempFile;

    fp = fopen(FILE_NAME, "r");
    tempFile = fopen("temp.txt", "w");

    if (fp == NULL || tempFile == NULL) {
        printf("Error updating account!\n");
        return;
    }

    while (fscanf(fp, "%s %d %f", temp.name, &temp.pin, &temp.balance) != EOF) 
	{
        if (strcmp(temp.name, user.name) == 0 && temp.pin == user.pin) 
		{
            fprintf(tempFile, "%s %d %.2f\n", user.name, user.pin, user.balance);
        } 
		else 
		{
            fprintf(tempFile, "%s %d %.2f\n", temp.name, temp.pin, temp.balance);
        }
    }

    fclose(fp);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);
}
