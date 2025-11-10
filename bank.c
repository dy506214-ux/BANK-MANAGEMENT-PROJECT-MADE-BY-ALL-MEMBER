#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================
//   STRUCTURE DEFINITION
// ==========================
struct Account {
    int acc_no;
    char name[50];
    float balance;
};

// ==========================
//   FUNCTION DECLARATIONS
// ==========================
void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void listAccounts();
void printLine();

// ==========================
//          MAIN FUNCTION
// ==========================
int main() {
    int choice;

    while (1) {
        printLine();
        printf("      BANK ACCOUNT MANAGEMENT SYSTEM \n");
        printLine();
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. List All Accounts\n");
        printf("6. Exit\n");
        printLine();
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: listAccounts(); break;
            case 6:
                printf("\nThank you for using Bank Management System!\n");
                exit(0);
            default:
                printf("\n❌ Invalid choice! Please enter between 1-6.\n");
        }
    }
    return 0;
}

// ==========================
//   CREATE NEW ACCOUNT
// ==========================
void createAccount() {
    FILE *fp;
    struct Account acc;

    fp = fopen("accounts.dat", "ab");  // Binary append mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);

    printf("\n✅ Account created successfully!\n");
}

// ==========================
//   DEPOSIT MONEY
// ==========================
void depositMoney() {
    FILE *fp;
    struct Account acc;
    int acc_no, found = 0;
    float amount;

    fp = fopen("accounts.dat", "r+b");
    if (fp == NULL) {
        printf("\n❌ No accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.acc_no == acc_no) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("\n✅ Amount Deposited Successfully!\n");
            printf("Updated Balance: ₹%.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found)
        printf("\n❌ Account not found!\n");
}

// ==========================
//   WITHDRAW MONEY
// ==========================
void withdrawMoney() {
    FILE *fp;
    struct Account acc;
    int acc_no, found = 0;
    float amount;

    fp = fopen("accounts.dat", "r+b");
    if (fp == NULL) {
        printf("\n❌ No accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.acc_no == acc_no) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount > acc.balance) {
                printf("\n⚠️  Insufficient Balance!\n");
            } else {
                acc.balance -= amount;
                fseek(fp, -sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("\n✅ Withdrawal Successful!\n");
                printf("Remaining Balance: ₹%.2f\n", acc.balance);
            }
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found)
        printf("\n❌ Account not found!\n");
}

// ==========================
//   CHECK BALANCE
// ==========================
void checkBalance() {
    FILE *fp;
    struct Account acc;
    int acc_no, found = 0;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("\n❌ No accounts found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc_no);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.acc_no == acc_no) {
            printf("\n🏦 Account Details\n");
            printLine();
            printf("Account Number: %d\n", acc.acc_no);
            printf("Account Holder: %s\n", acc.name);
            printf("Available Balance: ₹%.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);
    if (!found)
        printf("\n❌ Account not found!\n");
}

// ==========================
//   LIST ALL ACCOUNTS
// ==========================
void listAccounts() {
    FILE *fp;
    struct Account acc;
    int count = 0;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("\n❌ No accounts found!\n");
        return;
    }

    printf("\n========== ALL ACCOUNTS ==========\n");
    printf("Acc_No\tName\t\tBalance\n");
    printf("----------------------------------\n");

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        printf("%d\t%-10s\t₹%.2f\n", acc.acc_no, acc.name, acc.balance);
        count++;
    }

    if (count == 0)
        printf("No accounts to display.\n");

    fclose(fp);
}

// ==========================
//   HELPER FUNCTION
// ==========================
void printLine() {
    printf("===================================\n");
}
