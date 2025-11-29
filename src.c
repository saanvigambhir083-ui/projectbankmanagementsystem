// WAP to display banking services with the following options:
// 1. Enquiry
// 2. Open Account
// 3. Close Account
// 4. Deposit Money
// 5. Withdraw Money
// 6. Check Balance
// 7. Display Transaction History
// 8. Identify Defaulter
// 9. Exit
// BY - Mehak, Saanvi Gambhir

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int uniqueid;
    char name[50];
    float balance;
    char transactionhistory[1000];
    int transactioncount;
} Account;

// Save account to file
void saveaccount(Account acc)
{
    char filename[30];
    sprintf(filename, "account_%d.dat", acc.uniqueid);

    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        printf("Error saving account!\n");
        return;
    }

    fwrite(&acc, sizeof(Account), 1, file);
    fclose(file);
}

// Load account from file
Account loadaccount(int uniqueid)
{
    Account acc;
    memset(&acc, 0, sizeof(Account));

    char filename[30];
    sprintf(filename, "account_%d.dat", uniqueid);

    FILE *file = fopen(filename, "rb");
    if (!file)
        return acc;

    fread(&acc, sizeof(Account), 1, file);
    fclose(file);

    return acc;
}

// Option 1
void enquiry()
{
    printf("\nWelcome to the Banking Service!\n");
    printf("Available Services:\n");
    printf("1. Open Account\n");
    printf("2. Close Account\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Check Balance\n");
    printf("6. Transaction History\n");
    printf("7. Identify Defaulter\n");
    printf("Customer Care: 123-456-7890\n\n");
}

// Option 2
void openaccount()
{
    Account acc;

    printf("Enter Unique ID: ");
    scanf("%d", &acc.uniqueid);

    printf("Enter Name: ");
    scanf(" %[^\n]", acc.name);

    acc.balance = 0.0f;
    acc.transactioncount = 0;
    acc.transactionhistory[0] = '\0';

    saveaccount(acc);

    printf("\nAccount created successfully!\nYour Unique ID is: %d\n", acc.uniqueid);
}

// Option 3
void closeaccount()
{
    int id;
    printf("Enter Unique ID to close account: ");
    scanf("%d", &id);

    char filename[30];
    sprintf(filename, "account_%d.dat", id);

    if (remove(filename) == 0)
        printf("Account closed successfully!\n");
    else
        printf("Account not found!\n");
}

// Option 4
void depositmoney()
{
    int id;
    float amount;

    printf("Enter Unique ID: ");
    scanf("%d", &id);

    Account acc = loadaccount(id);

    if (acc.uniqueid == 0)
    {
        printf("Account not found!\n");
        return;
    }

    printf("Enter deposit amount (500–100000): ");
    scanf("%f", &amount);

    if (amount < 500 || amount > 100000)
    {
        printf("Invalid amount!\n");
        return;
    }

    acc.balance += amount;

    char entry[100];
    sprintf(entry, "Deposited: %.2f\n", amount);

    strncat(acc.transactionhistory, entry,
            sizeof(acc.transactionhistory) - strlen(acc.transactionhistory) - 1);

    acc.transactioncount++;

    saveaccount(acc);

    printf("Amount deposited successfully!\n");
}

// Option 5
void withdrawmoney()
{
    int id;
    float amount;

    printf("Enter Unique ID: ");
    scanf("%d", &id);

    Account acc = loadaccount(id);

    if (acc.uniqueid == 0)
    {
        printf("Account not found!\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > acc.balance)
    {
        printf("Insufficient balance!\n");
        return;
    }

    acc.balance -= amount;

    char entry[100];
    sprintf(entry, "Withdrew: %.2f\n", amount);

    strncat(acc.transactionhistory, entry,
            sizeof(acc.transactionhistory) - strlen(acc.transactionhistory) - 1);

    acc.transactioncount++;

    saveaccount(acc);

    printf("Amount withdrawn successfully!\n");
}

// Option 6
void checkbalance()
{
    int id;
    printf("Enter Unique ID: ");
    scanf("%d", &id);

    Account acc = loadaccount(id);

    if (acc.uniqueid == 0)
    {
        printf("Account not found!\n");
        return;
    }

    printf("Current Balance: %.2f\n", acc.balance);
}

// Option 7
void displaytransactionhistory()
{
    int id;
    printf("Enter Unique ID: ");
    scanf("%d", &id);

    Account acc = loadaccount(id);

    if (acc.uniqueid == 0)
    {
        printf("Account not found!\n");
        return;
    }

    if (strlen(acc.transactionhistory) == 0)
        printf("No transactions available.\n");
    else
        printf("\nTransaction History:\n%s", acc.transactionhistory);
}

// Option 8
void identifydefaulter()
{
    float minBalance;
    printf("Enter minimum balance: ");
    scanf("%f", &minBalance);

    printf("\nDefaulters:\n");

    for (int id = 1; id <= 9999; id++)
    {
        Account acc = loadaccount(id);
        if (acc.uniqueid != 0 && acc.balance < minBalance)
        {
            printf("ID: %d | Name: %s | Balance: %.2f\n",
                   acc.uniqueid, acc.name, acc.balance);
        }
    }
}

// Option 9
void exitprogram()
{
    printf("\n---------------------------\n");
    printf("Thank you for using our banking service!\n");
    printf("---------------------------\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n--------------------------------\n");
        printf("Banking Service Menu:\n");
        printf("1. Enquiry\n");
        printf("2. Open Account\n");
        printf("3. Close Account\n");
        printf("4. Deposit Money\n");
        printf("5. Withdraw Money\n");
        printf("6. Check Balance\n");
        printf("7. Transaction History\n");
        printf("8. Identify Defaulter\n");
        printf("9. Exit\n");
        printf("--------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1: enquiry(); break;
            case 2: openaccount(); break;
            case 3: closeaccount(); break;
            case 4: depositmoney(); break;
            case 5: withdrawmoney(); break;
            case 6: checkbalance(); break;
            case 7: displaytransactionhistory(); break;
            case 8: identifydefaulter(); break;
            case 9: exitprogram(); return 0;
            default: printf("Invalid choice! Try again.\n");
        }
     }
}