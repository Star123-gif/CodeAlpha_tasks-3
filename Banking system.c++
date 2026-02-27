#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Customer {
public:
    string name;
    int id;
    string address;
    Customer(string n, int i, string a) : name(n), id(i), address(a) {}
};

class Account {
public:
    int accountNumber;
    double balance;
    int customerId;
    vector<string> transactionHistory;
    Account(int accNum, int custId) : accountNumber(accNum), customerId(custId), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        transactionHistory.push_back("Deposit: +" + to_string(amount));
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transactionHistory.push_back("Withdrawal: -" + to_string(amount));
        } else {
            cout << "Insufficient balance!" << endl;
        }
    }

    void transfer(Account &toAccount, double amount) {
        if (amount <= balance) {
            balance -= amount;
            toAccount.balance += amount;
            transactionHistory.push_back("Transfer: -" + to_string(amount) + " to Acc " + to_string(toAccount.accountNumber));
            toAccount.transactionHistory.push_back("Transfer: +" + to_string(amount) + " from Acc " + to_string(accountNumber));
        } else {
            cout << "Insufficient balance for transfer!" << endl;
        }
    }

    void displayAccountInfo() {
        cout << "Account Number: " << accountNumber << "\nBalance: " << balance << endl;
        cout << "Transaction History:" << endl;
        for (const auto& transaction : transactionHistory) {
            cout << transaction << endl;
        }
    }
};

class Transaction {
public:
    int transactionId;
    string type;
    double amount;
    Transaction(int id, string t, double a) : transactionId(id), type(t), amount(a) {}
};

vector<Customer> customers;
vector<Account> accounts;
int accountCounter = 1001;

void createCustomer(string name, int id, string address) {
    customers.push_back(Customer(name, id, address));
    cout << "Customer created successfully!" << endl;
}

void createAccount(int customerId) {
    accounts.push_back(Account(accountCounter++, customerId));
    cout << "Account created with number: " << accountCounter - 1 << endl;
}

Account* findAccount(int accountNumber) {
    for (auto& acc : accounts) {
        if (acc.accountNumber == accountNumber) return &acc;
    }
    return nullptr;
}

int main() {
    int choice;
    do {
        cout << "\nBANKING SYSTEM MENU:\n1: Create Customer\n2: Create Account\n3: Deposit\n4: Withdraw\n5: Transfer\n6: View Account Info\n7: Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, address;
                int id;
                cout << "Enter name, id, address: ";
                cin >> name >> id >> address;
                createCustomer(name, id, address);
                break;
            }
            case 2: {
                int custId;
                cout << "Enter customer ID: ";
                cin >> custId;
                createAccount(custId);
                break;
            }
            case 3: {
                int accNum;
                double amount;
                cout << "Enter account number & deposit amount: ";
                cin >> accNum >> amount;
                Account* acc = findAccount(accNum);
                if (acc) acc->deposit(amount);
                break;
            }
            case 4: {
                int accNum;
                double amount;
                cout << "Enter account number & withdrawal amount: ";
                cin >> accNum >> amount;
                Account* acc = findAccount(accNum);
                if (acc) acc->withdraw(amount);
                break;
            }
            case 5: {
                int fromAcc, toAcc;
                double amount;
                cout << "Enter from-account, to-account & amount: ";
                cin >> fromAcc >> toAcc >> amount;
                Account *acc1 = findAccount(fromAcc), *acc2 = findAccount(toAcc);
                if (acc1 && acc2) acc1->transfer(*acc2, amount);
                break;
            }
            case 6: {
                int accNum;
                cout << "Enter account number: ";
                cin >> accNum;
                Account* acc = findAccount(accNum);
                if (acc) acc->displayAccountInfo();
                break;
            }
            case 7:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
