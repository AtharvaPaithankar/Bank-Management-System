#include<bits/stdc++.h>

using namespace std;

class User {
private:
    string username;
    string password;
    double balance;

public:
    User(string uname, string pass) : username(uname), password(pass), balance(0.0) {}

    string getUsername() const {
        return username;
    }

    bool authenticate(string pass) const {
        return password == pass;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "₹" << fixed << setprecision(2) << amount << " deposited successfully.\n";
        } else {
            cout << "Invalid amount. Deposit failed.\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount. Withdrawal failed.\n";
        } else if (amount > balance) {
            cout << "Insufficient balance. Withdrawal failed.\n";
        } else {
            balance -= amount;
            cout << "₹" << fixed << setprecision(2) << amount << " withdrawn successfully.\n";
        }
    }

    void checkBalance() const {
        cout << "Your current balance is ₹" << fixed << setprecision(2) << balance << endl;
    }
};

vector<User> users;
User* currentUser = nullptr;

User* findUser(const string& uname) {
    for (auto& user : users) {
        if (user.getUsername() == uname)
            return &user;
    }
    return nullptr;
}

void signUp() {
    string uname, pass;

    cout << "Choose a username: ";
    cin >> uname;

    if (findUser(uname)) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    cout << "Choose a password: ";
    cin >> pass;

    users.emplace_back(uname, pass);
    cout << "Sign up successful! You can now log in.\n";
}

bool login() {
    string uname, pass;
    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;

    User* user = findUser(uname);
    if (user && user->authenticate(pass)) {
        currentUser = user;
        cout << "Login successful. Welcome, " << uname << "!\n";
        return true;
    } else {
        cout << "Invalid username or password.\n";
        return false;
    }
}

void userDashboard() {
    int choice;
    do {
        cout << "\n--- Account Dashboard ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Check Balance\n";
        cout << "4. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                double amount;
                cout << "Enter amount to deposit: ₹";
                cin >> amount;
                currentUser->deposit(amount);
                break;
            }
            case 2: {
                double amount;
                cout << "Enter amount to withdraw: ₹";
                cin >> amount;
                currentUser->withdraw(amount);
                break;
            }
            case 3:
                currentUser->checkBalance();
                break;
            case 4:
                currentUser = nullptr;
                cout << "Logged out successfully.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);
}

int main() {
    int choice;

    do {
        cout << "\n==== Bank Management System ====\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signUp();
                break;
            case 2:
                if (login()) userDashboard();
                break;
            case 3:
                cout << "Thank you for using the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid input. Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
