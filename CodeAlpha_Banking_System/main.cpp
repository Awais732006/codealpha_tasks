// Task 4: Educational banking simulation. Data lasts for this program session.
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;
const long long MAX_MONEY = 100000000000LL; // PKR 1 billion, in paisa.

string readText(const string& prompt) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) throw runtime_error("Input ended.");
        if (line.find_first_not_of(" \t\r") != string::npos) return line;
        cout << "Input cannot be empty.\n";
    }
}
int readInt(const string& prompt, int low, int high) {
    while (true) {
        string line = readText(prompt); istringstream input(line); int value;
        if ((input >> value) && (input >> ws).eof() && value >= low && value <= high) return value;
        cout << "Enter a whole number from " << low << " to " << high << ".\n";
    }
}
// Parse decimal text directly into paisa to avoid floating-point money errors.
long long readMoney(const string& prompt) {
    while (true) {
        string s = readText(prompt);
        long long whole = 0, fraction = 0; int decimals = 0;
        bool dot = false, valid = true, digitSeen = false;
        for (char ch : s) {
            if (ch == '.' && !dot) { dot = true; continue; }
            if (ch < '0' || ch > '9') { valid = false; break; }
            digitSeen = true;
            if (!dot) {
                whole = whole * 10 + (ch - '0');
                if (whole > MAX_MONEY / 100) { valid = false; break; }
            } else {
                if (++decimals > 2) { valid = false; break; }
                fraction = fraction * 10 + ch - '0';
            }
        }
        if (decimals == 1) fraction *= 10;
        long long amount = whole * 100 + fraction;
        if (valid && digitSeen && amount > 0 && amount <= MAX_MONEY) return amount;
        cout << "Enter a positive amount up to 1000000000.00 with at most 2 decimal places.\n";
    }
}
string money(long long amount) {
    ostringstream out;
    out << "PKR " << amount / 100 << '.' << setw(2) << setfill('0') << amount % 100;
    return out.str();
}
class Customer {
public:
    int id; string name;
    Customer(int id, const string& name) : id(id), name(name) {}
};
class Transaction {
public:
    int id; string type; int from, to; long long amount;
    Transaction(int id, const string& type, int from, int to, long long amount)
        : id(id), type(type), from(from), to(to), amount(amount) {}
};
class Account {
public:
    int id, customerId; long long balance;
    Account(int id, int owner) : id(id), customerId(owner), balance(0) {}
};
class Bank {
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> history;
    int nextCustomer = 1, nextAccount = 1001, nextTransaction = 1;
    Account* findAccount(int id) {
        for (Account& a : accounts) if (a.id == id) return &a;
        return nullptr;
    }
    Customer* findCustomer(int id) {
        for (Customer& c : customers) if (c.id == id) return &c;
        return nullptr;
    }
    Account* selectAccount() {
        Account* a = findAccount(readInt("Account ID: ", 1001, 1000000000));
        if (!a) cout << "Account not found.\n";
        return a;
    }
public:
    void createCustomer() {
        string name = readText("Customer name: ");
        customers.push_back(Customer(nextCustomer++, name));
        cout << "Customer created. ID: " << customers.back().id << '\n';
    }
    void renameCustomer() {
        Customer* c = findCustomer(readInt("Customer ID: ", 1, 1000000000));
        if (!c) { cout << "Customer not found.\n"; return; }
        c->name = readText("New customer name: "); cout << "Customer updated.\n";
    }
    void createAccount() {
        int id = readInt("Customer ID: ", 1, 1000000000);
        if (!findCustomer(id)) { cout << "Customer not found.\n"; return; }
        accounts.push_back(Account(nextAccount++, id));
        cout << "Account created. ID: " << accounts.back().id << '\n';
    }
    void changeBalance(bool deposit) {
        Account* a = selectAccount(); if (!a) return;
        long long amount = readMoney("Amount (PKR): ");
        if (!deposit && amount > a->balance) { cout << "Insufficient funds.\n"; return; }
        if (deposit && amount > MAX_MONEY - a->balance) { cout << "Balance limit exceeded.\n"; return; }
        a->balance += deposit ? amount : -amount;
        history.push_back(Transaction(nextTransaction++, deposit ? "Deposit" : "Withdrawal",
                                      deposit ? 0 : a->id, deposit ? a->id : 0, amount));
        cout << "Success. Balance: " << money(a->balance) << '\n';
    }
    void transfer() {
        int fromId = readInt("Source account ID: ", 1001, 1000000000);
        int toId = readInt("Destination account ID: ", 1001, 1000000000);
        Account* from = findAccount(fromId); Account* to = findAccount(toId);
        if (!from || !to) { cout << "Account not found.\n"; return; }
        if (fromId == toId) { cout << "Choose two different accounts.\n"; return; }
        long long amount = readMoney("Amount (PKR): ");
        if (amount > from->balance) { cout << "Insufficient funds.\n"; return; }
        if (amount > MAX_MONEY - to->balance) { cout << "Destination balance limit exceeded.\n"; return; }
        from->balance -= amount; to->balance += amount;
        history.push_back(Transaction(nextTransaction++, "Transfer", fromId, toId, amount));
        cout << "Transfer successful. Source balance: " << money(from->balance)
             << " | Destination balance: " << money(to->balance) << '\n';
    }
    void showAccount() {
        Account* a = selectAccount(); if (!a) return;
        cout << "Account: " << a->id << " | Customer: " << findCustomer(a->customerId)->name
             << " | Balance: " << money(a->balance) << '\n';
    }
    void showHistory() {
        Account* a = selectAccount(); if (!a) return;
        int shown = 0;
        cout << "Recent transactions (newest first, up to 10):\n";
        for (auto it = history.rbegin(); it != history.rend() && shown < 10; ++it)
            if (it->from == a->id || it->to == a->id) {
                cout << '#' << it->id << ' ' << it->type << " | From: " << it->from
                     << " | To: " << it->to << " | " << money(it->amount) << '\n';
                ++shown;
            }
        if (!shown) cout << "No transactions yet.\n";
        cout << "Account ID 0 represents cash entering or leaving the bank.\n";
    }
    void listCustomers() {
        if (customers.empty()) cout << "No customers yet.\n";
        for (const Customer& c : customers) cout << c.id << " | " << c.name << '\n';
    }
    void closeAccount() {
        int id = readInt("Account ID to close: ", 1001, 1000000000);
        for (auto it = accounts.begin(); it != accounts.end(); ++it)
            if (it->id == id) {
                if (it->balance != 0) { cout << "Withdraw or transfer the remaining balance first.\n"; return; }
                accounts.erase(it); cout << "Account closed.\n"; return;
            }
        cout << "Account not found.\n";
    }
};
int main() {
    Bank bank;
    cout << "BANKING SYSTEM - educational session-only simulation\n";
    try {
        while (true) {
            cout << "\n1 Create customer\n2 Create account\n3 Deposit\n4 Withdraw\n5 Transfer\n"
                    "6 View account\n7 Recent transactions\n8 List customers\n9 Rename customer\n10 Close account\n0 Exit\n";
            int choice = readInt("Choice: ", 0, 10);
            switch (choice) {
                case 0: cout << "Goodbye. Session data cleared.\n"; return 0;
                case 1: bank.createCustomer(); break;
                case 2: bank.createAccount(); break;
                case 3: bank.changeBalance(true); break;
                case 4: bank.changeBalance(false); break;
                case 5: bank.transfer(); break;
                case 6: bank.showAccount(); break;
                case 7: bank.showHistory(); break;
                case 8: bank.listCustomers(); break;
                case 9: bank.renameCustomer(); break;
                case 10: bank.closeAccount(); break;
            }
        }
    } catch (const exception& e) { cerr << e.what() << '\n'; return 1; }
}
