#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int accNo;
    char name[50];
    float balance;
};

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "ab");

    printf("Enter account number: ");
    scanf("%d", &acc.accNo);
    printf("Enter name: ");
    scanf(" %[^\n]", acc.name);
    printf("Enter initial balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);
    printf("Account created successfully!\n");
}

void displayAccounts() {
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb");

    printf("\n--- All Accounts ---\n");
    while (fread(&acc, sizeof(acc), 1, fp)) {
        printf("Account No: %d\n", acc.accNo);
        printf("Name: %s\n", acc.name);
        printf("Balance: %.2f\n", acc.balance);
        printf("----------------------\n");
    }

    fclose(fp);
}

void depositMoney() {
    int accNo, found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("Enter account number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            found = 1;
            printf("Deposit successful!\n");
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

void withdrawMoney() {
    int accNo, found = 0;
    float amount;
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb+");

    printf("Enter account number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount <= acc.balance) {
                acc.balance -= amount;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("Withdrawal successful!\n");
            } else {
                printf("Insufficient balance!\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

void searchAccount() {
    int accNo, found = 0;
    struct Account acc;
    FILE *fp = fopen("bank.dat", "rb");

    printf("Enter account number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accNo == accNo) {
            printf("Account No: %d\n", acc.accNo);
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n--- Bank Management System ---\n");
        printf("1. Create Account\n");
        printf("2. Display All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Search Account\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: searchAccount(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}
