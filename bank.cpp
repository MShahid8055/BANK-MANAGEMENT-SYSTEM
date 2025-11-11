#include <iostream>
#include <fstream>
using namespace std;

// Template function (just to show template use)
template <class T>
T show(T x) {
    return x;
}

// Account class
class Account {
private:
    int accNo;
    string name;
    double balance;

public:
    // Constructor
    Account(int a = 0, string n = "", double b = 0) {
        accNo = a;
        name = n;
        balance = b;
    }

    // Friend function (can access private members)
    friend void display(Account A);

    // Deposit function
    void deposit(double amt) {
        balance += amt;
    }

    // Withdraw with exception handling
    void withdraw(double amt) {
        if (amt <= balance) {
            balance -= amt;
        } else {
            throw "Insufficient Balance";
        }
    }

    int getAccNo() { return accNo; }
    double getBalance() { return balance; }
    string getName() { return name; }
};

// Friend function to show account details
void display(Account A) {
    cout << A.getAccNo() << "\t" << A.getName() << "\t" << A.getBalance() << endl;
}

// Bank class contains multiple accounts (aggregation)
class Bank {
public:
    Account a[10];
    int count;

    Bank() {
        count = 0;
    }

    // Add new account
    void addAccount(int no, string nm, double bal) {
        a[count] = Account(no, nm, bal);
        count++;
    }

    // Search account
    int search(int no) {
        for (int i = 0; i < count; i++) {
            if (a[i].getAccNo() == no)
                return i;
        }
        throw "Account Not Found";
    }

    // Show all accounts
    void showAll() {
        cout << "\nAccNo\tName\tBalance\n";
        for (int i = 0; i < count; i++) {
            display(a[i]);
        }
    }

    // Save data in file
    void save() {
        ofstream fout("bankdata.txt");
        for (int i = 0; i < count; i++) {
            fout << a[i].getAccNo() << " " << a[i].getBalance() << endl;
        }
        fout.close();
    }
};

int main() {
    Bank b;

    // Adding sample accounts
    b.addAccount(101, "Shahid", 5000);
    b.addAccount(102, "Rahul", 3000);

    int ch, no, pos;
    double amt;

    do {
        cout << "\n1. Show Accounts\n2. Deposit\n3. Withdraw\n4. Save & Exit\nEnter Choice: ";
        cin >> ch;

        if (ch == 1) {
            b.showAll();
        }
        else if (ch == 2) {
            try {
                cout << "Enter Account No: ";
                cin >> no;
                pos = b.search(no);
                cout << "Enter Amount: ";
                cin >> amt;
                b.a[pos].deposit(amt);
            }
            catch(const char* msg) {
                cout << msg << endl;
            }
        }
        else if (ch == 3) {
            try {
                cout << "Enter Account No: ";
                cin >> no;
                pos = b.search(no);
                cout << "Enter Amount: ";
                cin >> amt;
                b.a[pos].withdraw(amt);
            }
            catch(const char* msg) {
                cout << msg << endl;
            }
        }
        else if (ch == 4) {
            b.save();
            cout << "\nData Saved. Exiting...\n";
        }

    } while (ch != 4);

    return 0;
}