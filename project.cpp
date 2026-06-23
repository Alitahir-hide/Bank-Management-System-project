#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include<iomanip>
#include <fstream>
using namespace std;

class Account {
public:


    int number;  // Security number for password recovery
    string name;
    int account_number;
    int password;
    double balance;  // Balance for the account
    vector<string> transactions;  // Track recent transactions

    Account() {
        number = 0;
        name = "";
        account_number = 0;
        password = 0;
        balance = 0.0;
    }
    Account(int num, string acc_name, int acc_num, int acc_password) {
        number = num;
        name = acc_name;
        account_number = acc_num;
        password = acc_password;
        balance = 0.0;
    }

    void print_account() const {
        cout << "Name: " << name << "\tAccount Number: " << account_number << "\tBalance: $" << balance << "\n";
    }

    void statementGeneration() const {
        cout << setfill('=') << setw(50) << "=" << endl;
        cout << "Account Statement" << endl;
        cout << setfill('=') << setw(50) << "=" << endl;

        cout << setfill(' ') << left << setw(20) << "Name:" << right << setw(30) << name << endl;
        cout << setfill(' ') << left << setw(20) << "Account Number:" << right << setw(30) << account_number << endl;
        cout << setfill(' ') << left << setw(20) << "Balance:" << right << setw(22) << fixed << setprecision(2) << "$" << balance << endl;

        cout << setfill('=') << setw(50) << "=" << endl;
        cout << "Recent Transactions" << endl;
        cout << setfill('=') << setw(50) << "=" << endl;

        for (auto& transaction : transactions) {
            cout << transaction << endl;
        }

        cout << setfill('=') << setw(50) << "=" << endl;
    }


    bool verify_password(int& input_password) const {
        return password == input_password;
    }

    bool verify_security_number(int sec_number) const {
        return number == sec_number;
    }

    void reset_name(string& name) {
        this->name = name;
    }
    void reset_password(int& pasword) {
        this->password = pasword;
    }


    void deposit(double amount) {
        balance += amount;
        transactions.push_back("Deposit: $" + to_string(amount));
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        else {
            balance -= amount;
            transactions.push_back("Withdraw: $" + to_string(amount));
            return true;
        }
    }

    void print_recent_transactions() const {
        cout << "Recent transactions for account " << account_number << ":\n";
        for (auto& transaction : transactions) {
            cout << transaction << "\n";
        }
    }

    int get_account_number() const {
        return account_number;
    }

    int get_security_number() const {
        return number;
    }

    double get_balance() const {
        return balance;
    }
};



class BankSystem {
private:
    vector<Account> user_accounts;
    vector<Account> admin_accounts;
    int user_account_number_ssed = 5232001;
    int admin_account_number_ssed = 4232001;
public:
    friend void Header();

    void user_info() {
        for (int i = 0; i < user_accounts.size(); ++i) {
            user_accounts[i].print_account();
            user_accounts[i].print_recent_transactions();
            cout << "\n\n";
        }
    }

    template <typename T>
    T check_input() const {
        T num;
        while (true) {
            cin >> num;
            if (cin.fail()) {
                cout << "Please enter a valid input: ";
                cin.clear();
                cin.ignore(100, '\n');
            }
            else {
                break;
            }
        }
        return num;
    }

    string check_string() const {
        string n;
        while (true) {
            cin >> n;

            if ((n >= "A" && n <= "Z") || (n >= "a" && n <= "z")) {
                return n;
            }
            else {
                cout << "Only A-to-Z allowed\n";
            }
        }
    }

    int search_account(const vector<Account>& accounts, int id) const {
        for (int i = 0; i < accounts.size(); ++i) {
            if (accounts[i].get_account_number() == id)
                return i;
        }
        return -1;
    }

    int search_security_number(const vector<Account>& accounts, int id) const {
        for (int i = 0; i < accounts.size(); ++i) {
            if (accounts[i].get_security_number() == id)
                return i;
        }
        return -1;
    }

    void statementGeneration() const {
        cout << "Please enter your account number: ";
        int account_number;
        account_number = check_input<int>();
        int index;
        index = search_account(user_accounts, account_number);
        if (index != -1) {
            user_accounts[index].statementGeneration();
        }
        else {
            cout << "Account number not found.\n";
        }
    }

    void delay(int milliseconds) const {
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }

    void clearPreviousPosition(int objectHeight) const {
        for (int i = 0; i < objectHeight; ++i) {
            cout << "\033[F";  // ANSI escape code to move cursor up one line
        }
    }

    void moveObjectAcrossScreen(const char* object[], int objectHeight, int objectWidth, int screenWidth, int delayTime) const {
        for (int position = 0; position <= screenWidth - objectWidth; ++position) {
            for (int i = 0; i < objectHeight; ++i) {
                for (int j = 0; j < position; ++j) {
                    cout << ' ';
                }
                cout << object[i] << endl;
            }
            delay(delayTime);
            clearPreviousPosition(objectHeight);
        }
    }

    void clear_screen(int delayTime) const {
        int choice;
        //cout << "Press any integer to change the screen: ";
        //choice = check_input<int>();

        const char* arrow[] = {
            "#######################",
            "#      $MONEY$        #",
            "#######################"
        };
        int objectHeight = sizeof(arrow) / sizeof(arrow[0]);
        int objectWidth = strlen(arrow[0]);
        int screenWidth = 80;  // Adjust the width of the screen as needed

        moveObjectAcrossScreen(arrow, objectHeight, objectWidth, screenWidth, delayTime);

        system("cls");
    }




    void create_account(int choice) {
        cout << "Please enter your security number: ";
        int security_number;
        security_number = check_input<int>();
        int index;
        index = search_security_number(user_accounts, security_number);

        if (index == -1) {
            cout << "\nPlease enter your name: ";
            string name = check_string();
            cout << "Please set your password: ";
            int password;
            cin >> password;
            int account_number;
            if (choice == 1) {
                account_number = user_accounts.size() + user_account_number_ssed;
            }
            else {
                account_number = admin_accounts.size() + admin_account_number_ssed;
            }
            Account new_account(security_number, name, account_number, password);

            if (choice == 1) {
                cout << "Account created. Your account number is " << account_number << "\n";
                user_accounts.push_back(new_account);
                system("pause");

                clear_screen(10);
                run();
            }
            else {
                cout << "Admin account created. Your account number is " << account_number << "\n";
                admin_accounts.push_back(new_account);
                cout << "press 1 to see all the users informations\nif you want to exit press any other number.";
                int a;
                a = check_input<int>();
                if (a == 1) {
                    clear_screen(10);
                    user_info();
                }
            }
        }
        else {
            cout << "\nSecurity number already exists.";
            system("pause");
        }
    }

    void login() {
        int choice;
        cout << "1-User\n2-Admin\n";
        choice = check_input<int>();
        cout << "Please enter your account number: ";
        int account_number;
        account_number = check_input<int>();
        int index;
        int input_password;

        if (choice == 1) {
            index = search_account(user_accounts, account_number);

            if (index != -1) {

            back:
                cout << "Please enter your password: ";
                cin >> input_password;
                if (user_accounts[index].verify_password(input_password)) {
                    cout << "Login successful!\n";
                    user_accounts[index].print_account();
                    clear_screen(10);
                    run();

                }
                else {
                    cout << "Incorrect password.\n1-enter again\nany integer to go back;\n";
                    int a;
                    cin >> a;
                    if (a == 1) {
                        goto back;
                    }
                    else
                        clear_screen(10);

                }
            }
        }
        else if (choice == 2) {
            int index1 = search_account(admin_accounts, account_number);
            if (index1 != -1) {
                cout << "Please enter your password: ";
                cin >> input_password;

                if (admin_accounts[index1].verify_password(input_password)) {
                    cout << "Login successful!\n";
                    admin_accounts[index1].print_account();
                    clear_screen(10);
                    run();

                }
                else {
                    cout << "Incorrect password.\n1-enter again\nany integer to go back;\n";
                    int a;
                    cin >> a;
                    if (a == 1) {
                        goto back;
                    }
                    else
                        clear_screen(10);

                }
            }
        }
        else {
            cout << "Account number not found.\n";
        }
    }

    void reset_account() {
        cout << "Please enter your account number: ";

        int security_number, acc_num;
        int index2, index1;
        acc_num = check_input<int>();
        index1 = search_account(user_accounts, acc_num);

        if (index1 != -1) {
        back:
            cout << "\nplaese neter your security number: ";
            security_number = check_input<int>();
            index2 = search_security_number(user_accounts, security_number);
            cout << "\n1-Pasword\n2-Name\n";
            int new_pasword, ch;
            string new_name;
            string n;
            ch = check_input<int>();
            if (ch == 1) {
                cout << "Please enter your new password: ";
                cin >> new_pasword;
                user_accounts[index2].reset_password(new_pasword);
                cout << "Password reset successful.\nif you want to update name press Y/any alphabet";

                n = check_string();

                if (n == "Y" || n == "y") {
                    cout << "Please enter your new name: ";
                    cin >> new_name;
                    user_accounts[index2].reset_name(new_name);
                }
                else if (ch == 2) {
                    cout << "Please enter your new name: ";
                    cin >> new_name;
                    user_accounts[index2].reset_name(new_name);
                    cout << "name update successfuly.\nif you want to update password press Y/any_alphabet";
                    if (n == "Y" || n == "y") {
                        cout << "Please enter your new password: ";
                        cin >> new_pasword;
                        user_accounts[index2].reset_password(new_pasword);
                    }
                    else
                        cout << "please enter the correct number.";
                    goto back;
                }

            }
            else {
                cout << "Security number not found.\n";
            }
        }
    }

    void deposit() {
        cout << "Please enter your account number: ";
        int account_number = check_input<int>();
        int index = search_account(user_accounts, account_number);
        if (index != -1) {
            cout << "Enter the amount to deposit: ";

            double amount = check_input<double>();

            user_accounts[index].deposit(amount);

            cout << "Deposit successful. Current balance: $" << user_accounts[index].get_balance() << "\n";
        }
        else {
            cout << "Account number not found.\n";
        }
    }

    void withdraw() {
        cout << "Please enter your account number: ";
        int account_number = check_input<int>();
        int index = search_account(user_accounts, account_number);
        if (index != -1) {
            cout << "Enter the amount to withdraw: ";
            double amount = check_input<double>();
            if (user_accounts[index].withdraw(amount)) {
                cout << "Withdrawal successful. Current balance: $" << user_accounts[index].get_balance() << "\n";
            }
            else {
                cout << "Insufficient funds.\n";
            }
        }
        else {
            cout << "Account number not found.\n";
        }
    }

    void print_recent_transactions() {
        cout << "Please enter your account number: ";
        int account_number = check_input<int>();

        int index = search_account(user_accounts, account_number);

        if (index != -1) {
            user_accounts[index].print_recent_transactions();
        }
        else {
            cout << "Account number not found.\n";
        }
    }

    void delete_account() {
        int account_number, choice, index, ch2;
        while (true) {
            cout << "1-User account.\n2-Admin account\n";
            choice = check_input<int>();
        back:

            cout << "\nplease enter the account number.\n";
            account_number = check_input<int>();
            if (choice == 1) {
                index = search_account(user_accounts, account_number);
                if (index != -1) {
                    user_accounts.erase(user_accounts.begin() + index);
                    cout << "User account " << account_number << " deleted successfully.\n";
                    system("pause");
                    clear_screen(10);
                    break;
                }
                else {
                    cout << "invalid account number.";
                    cout << "if you want to enter again press 1 otherwise any number\n";
                    ch2 = check_input<int>();
                    if (ch2 == 1) {
                        goto back;
                    }
                    else {
                        clear_screen(10);
                        break;
                    }
                }
            }
            else if (choice == 2) {
                index = search_account(admin_accounts, account_number);
                if (index != -1) {
                    admin_accounts.erase(admin_accounts.begin() + index);
                    cout << "Admin account " << account_number << " deleted successfully.\n";
                    system("pause");
                    clear_screen(10);
                    break;
                }
                else
                {
                    cout << "Account number not found.\n";
                    cout << "if you want to enter again press 1 otherwise any number\n";
                    ch2 = check_input<int>();
                    if (ch2 == 1) {
                        goto back;
                    }
                    else {
                        clear_screen(10);
                        break;
                    }
                }
            }
            else
                cout << "please enter the right choice.";

        }

    }
    void run() {
        int choice;
        int delayTime = 10;

        while (true) {
            system("color F5");
            cout << setfill('#') << setw(82);

            cout << "\n# 1. Deposit                   " << setfill(' ') << setw(20) << "#\n";
            cout << "# 2. Withdraw                  " << setfill(' ') << setw(20) << "#\n";
            cout << "# 3. Print Recent Transactions " << setfill(' ') << setw(20) << "#\n";
            cout << "# 4. Generate Account Statement" << setfill(' ') << setw(20) << "#\n";
            cout << "# 5. Logout                    " << setfill(' ') << setw(20) << "#\n";
            cout << setfill('#') << setw(51) << "\n";

            choice = check_input<int>();


            if (choice == 1) {
                deposit();
                clear_screen(10);

            }
            else if (choice == 2) {
                withdraw();
                clear_screen(10);

            }
            else if (choice == 3) {
                print_recent_transactions();
                clear_screen(10);

            }
            else if (choice == 4) {
                statementGeneration();
                clear_screen(10);

            }
            else if (choice == 5) {
                cout << "Logging out...\n";
                clear_screen(delayTime);
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
            clear_screen(delayTime);
        }
    }




    void save_data() const {
        ofstream user_file("user_data.txt");
        ofstream admin_file("admin_data.txt");

        if (user_file.is_open() && admin_file.is_open()) {
            // Save user accounts
            user_file << user_accounts.size() << "\n";
            for (const auto& account : user_accounts) {
                user_file << account.get_security_number() << "\n"
                    << account.name << "\n"
                    << account.get_account_number() << "\n"
                    << account.password << "\n"
                    << account.get_balance() << "\n"
                    << account.transactions.size() << "\n";
                for (const auto& transaction : account.transactions) {
                    user_file << transaction << "\n";
                }
            }

            // Save admin accounts
            admin_file << admin_accounts.size() << "\n";
            for (const auto& account : admin_accounts) {
                admin_file << account.get_security_number() << "\n"
                    << account.name << "\n"
                    << account.get_account_number() << "\n"
                    << account.password << "\n"
                    << account.get_balance() << "\n"
                    << account.transactions.size() << "\n";
                for (const auto& transaction : account.transactions) {
                    admin_file << transaction << "\n";
                }
            }

            user_file.close();
            admin_file.close();
        }
        else {
            cerr << "Error opening file for saving data.\n";
        }
    }

    void load_data() {
        ifstream user_file("user_data.txt");
        ifstream admin_file("admin_data.txt");

        if (user_file.is_open() && admin_file.is_open()) {
            // Load user accounts
            int user_count;
            user_file >> user_count;
            user_file.ignore();
            user_accounts.resize(user_count);
            for (int i = 0; i < user_count; ++i) {
                int transaction_count;
                user_file >> user_accounts[i].number;
                user_file.ignore();
                getline(user_file, user_accounts[i].name);
                user_file >> user_accounts[i].account_number >> user_accounts[i].password >> user_accounts[i].balance;
                user_file >> transaction_count;
                user_file.ignore();
                user_accounts[i].transactions.resize(transaction_count);
                for (int j = 0; j < transaction_count; ++j) {
                    getline(user_file, user_accounts[i].transactions[j]);
                }
            }

            // Load admin accounts
            int admin_count;
            admin_file >> admin_count;
            admin_file.ignore();
            admin_accounts.resize(admin_count);
            for (int i = 0; i < admin_count; ++i) {
                int transaction_count;
                admin_file >> admin_accounts[i].number;
                admin_file.ignore();
                getline(admin_file, admin_accounts[i].name);
                admin_file >> admin_accounts[i].account_number >> admin_accounts[i].password >> admin_accounts[i].balance;
                admin_file >> transaction_count;
                admin_file.ignore();
                admin_accounts[i].transactions.resize(transaction_count);
                for (int j = 0; j < transaction_count; ++j) {
                    getline(admin_file, admin_accounts[i].transactions[j]);
                }
            }

            user_file.close();
            admin_file.close();
        }
        else {
            cerr << "Error opening file for loading data.\n";
        }
    }

};
 void Header() {
    cout << setw(120) << setfill('-') << " " << endl;
    cout << setw(120) << setfill('-') << " " << endl;
    cout << setw(73) << setfill('-') << " BAHRIA BANKING SYSTEM " << setw(47) << setfill('-') << " " << endl;
    cout << setw(120) << setfill('-') << " " << endl;
    cout << setw(120) << setfill('-') << " " << endl << endl << endl;
}

int main() {
    
    BankSystem bankSystem;
    bankSystem.load_data();  // Load data at the start
    int choice;
    while (true) {

        system("color F0");
        system("cls");
       Header();

        cout << "\n\n                " << setfill('*') << setw(60) << "*" << endl;

        cout << "                " << "*" << setfill(' ') << setw(58) << " " << "*" << endl;
        cout << "                " << setfill(' ') << setw(29) << "*------- 1. Create User Account -------" << setw(21) << "*" << endl;
        cout << "                " << "*" << setfill(' ') << setw(28) << "------- 2. Create Admin Account -------" << setw(20) << "*" << endl;
        cout << "                " << "*" << setfill(' ') << setw(20) << "------- 3. Login -------" << setw(35) << "*" << endl;
        cout << "                " << "*" << setfill(' ') << setw(28) << "------- 4. Reset Account -------" << setw(27) << "*" << endl;
        cout << "                " << "*" << setfill(' ') << setw(31) << "------- 5. Delete Account -------" << setw(26) << "*" << endl;
        cout << "                " << "*" << setfill(' ') << setw(15) << "------- 6. Exit -------" << setw(36) << "*" << endl;
        cout << "                " << "*" << setfill(' ') << setw(58) << " " << "*" << endl;
        cout << "                " << setfill('*') << setw(60) << "*" << endl;
        cout << "                " << "Enter your choice: ";
        choice = bankSystem.check_input<int>();

        system("cls");
        if (choice == 1 || choice == 2) {
            bankSystem.create_account(choice);
        }
        else if (choice == 3) {
            bankSystem.login();
        }
        else if (choice == 4) {
            bankSystem.reset_account();
        }
        else if (choice == 5) {
            bankSystem.delete_account();
        }
        else if (choice == 6) {
            cout << "Exiting the system. Goodbye!\n";
            bankSystem.save_data();  // Save data before exiting
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    system("pause");
    return 0;
}



