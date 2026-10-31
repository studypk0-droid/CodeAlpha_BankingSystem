#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Transaction class to store transaction details
class Transaction {
public:
    string type;
    double amount;

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }

    void display() {
        cout << "Type: " << type << " | Amount: $" << amount << endl;
    }
};

// Account class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNo, double initialBalance) {
        accountNumber = accNo;
        balance = initialBalance;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            history.push_back(Transaction("Deposit", amount));
            cout << "Success! Deposited $" << amount << endl;
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            history.push_back(Transaction("Withdrawal", amount));
            cout << "Success! Withdrawn $" << amount << endl;
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    void transfer(Account &targetAccount, double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            targetAccount.balance += amount;
            history.push_back(Transaction("Transfer Out", amount));
            targetAccount.history.push_back(Transaction("Transfer In", amount));
            cout << "Success! Transferred $" << amount << " to Account No: " << targetAccount.getAccountNumber() << endl;
        } else {
            cout << "Transfer failed! Check balance or amount.\n";
        }
    }

    void showTransactionHistory() {
        cout << "\n--- Transaction History ---\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (size_t i = 0; i < history.size(); i++) {
                history[i].display();
            }
        }
    }
};

// Customer class
class Customer {
private:
    string name;
    int customerId;
public:
    Account account;

    Customer(string n, int id, int accNo, double initialBalance) : account(accNo, initialBalance) {
        name = n;
        customerId = id;
    }

    void displayInfo() {
        cout << "\n--- Customer & Account Info ---\n";
        cout << "Name: " << name << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Account Number: " << account.getAccountNumber() << endl;
        cout << "Current Balance: $" << account.getBalance() << endl;
    }
};

int main() {
    // Demo ke liye do customers create kiye hain (Ali aur Ahmad)
    Customer c1("Ali", 101, 1001, 5000.0);
    Customer c2("Ahmad", 102, 1002, 2000.0);

    int choice;
    do {
        cout << "\n==============================\n";
        cout << "      BANKING SYSTEM MENU     \n";
        cout << "==============================\n";
        cout << "1. View Account Info (Ali)\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Transfer Money (Ali to Ahmad)\n";
        cout << "5. View Transaction History\n";
        cout << "6. Exit\n";
        cout << "Apni choice enter karein (1-6): ";
        cin >> choice;

        double amount;
        switch (choice) {
            case 1:
                c1.displayInfo();
                break;
            case 2:
                cout << "Enter deposit amount: ";
                cin >> amount;
                c1.account.deposit(amount);
                break;
            case 3:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                c1.account.withdraw(amount);
                break;
            case 4:
                cout << "Enter transfer amount to Ahmad: ";
                cin >> amount;
                c1.account.transfer(c2.account, amount);
                break;
            case 5:
                c1.account.showTransactionHistory();
                break;
            case 6:
                cout << "Program exit ho raha hai. !\n";
                break;
            default:
                cout << "Ghalat choice! Dobara koshish karein.\n";
        }
    } while (choice != 6);

    return 0;
}