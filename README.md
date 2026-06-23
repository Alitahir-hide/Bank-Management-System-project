# 🏦 Bank Management System

A console-based Bank Management System developed in **C++** using **Object-Oriented Programming (OOP)** concepts. The system allows users and administrators to perform various banking operations such as account creation, deposits, withdrawals, transfers, account management, and statement generation.

---

## 📖 Project Overview

This project simulates a simple banking environment where users can manage their accounts and perform financial transactions securely. Administrators have additional privileges to create, delete, and reset accounts.

The system stores account information and transaction history using text files.

---

## ✨ Features

### User Features
- Create a bank account
- Login securely
- Deposit money
- Withdraw money
- Transfer funds between accounts
- View recent transactions
- Generate account statements
- Reset account information

### Admin Features
- Create admin accounts
- View user information
- Delete accounts
- Reset user/admin accounts
- Manage system users

---

## 🏗️ System Architecture

### Account Class
The `Account` class represents a bank account and contains:

#### Attributes
- Security Number
- Account Holder Name
- Account Number
- Password
- Balance
- Transaction History

#### Functions
- Deposit Funds
- Withdraw Funds
- Verify Password
- Verify Security Number
- Generate Statements
- Print Account Information
- Print Recent Transactions

---

### BankSystem Class
The `BankSystem` class controls the complete banking system.

#### Main Functions

| Function | Description |
|-----------|-------------|
| `run()` | Executes the main banking menu |
| `login()` | Handles user authentication |
| `create_account()` | Creates new user/admin accounts |
| `deposit()` | Deposits money into an account |
| `withdraw()` | Withdraws money from an account |
| `transfer()` | Transfers money between accounts |
| `statementGeneration()` | Generates account statements |
| `print_recent_transactions()` | Displays transaction history |
| `delete_account()` | Deletes existing accounts |
| `reset_account()` | Updates account information |
| `Header()` | Displays system header |

---

## 📂 Data Storage

The project uses text files for storing data.

### Files Used

#### Users_Data.txt
Stores:
- Account Number
- Name
- Password
- Security Code
- Balance

#### Admins_Data.txt
Stores:
- Account Number
- Name
- Password
- Security Code

#### Withdrawl_History.txt
Stores:
- Account Number
- Previous Balance
- Withdrawn Amount

#### Deposit_History.txt
Stores:
- Account Number
- Previous Balance
- Deposited Amount

---

## 🎯 OOP Concepts Implemented

### 1. Inheritance
Inheritance is used to establish relationships between banking-related classes.

### 2. Encapsulation
Data and functions are grouped together within classes to maintain data security and organization.

### 3. Abstraction
Complex banking operations are hidden behind simple function calls such as:
- Deposit
- Withdraw
- Transfer
- Statement Generation

### 4. Classes and Objects
The project is built around:
- `Account`
- `BankSystem`

Objects are created to represent users and administrators.

### 5. Information Hiding
Sensitive information such as passwords and security numbers is accessed through controlled member functions.

### 6. Data Encapsulation
Account data is manipulated only through class methods to ensure consistency and security.

---

## 🛠 Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- Standard Template Library (STL)
  - Vector
  - String
- Console Interface

---

## 🚀 How to Run

### Requirements
- C++ Compiler (GCC, MinGW, Visual Studio, etc.)

### Steps

1. Clone or download the project.
2. Open the project in your preferred C++ IDE.
3. Compile the source code:

```bash
g++ main.cpp -o BankManagementSystem
```

4. Run the executable:

```bash
./BankManagementSystem
```

---

## 📋 How to Use

1. Start the application.
2. Create a User or Admin account.
3. Login using your credentials.
4. Choose an operation from the menu:
   - Deposit
   - Withdraw
   - Transfer
   - View Transactions
   - Generate Statement
   - Account Management
5. Logout or exit the system when finished.

---

## 📸 Sample Functionalities

### Account Creation
Creates a new account and generates a unique account number.

### Deposit
Adds money to the selected account.

### Withdrawal
Removes money while ensuring sufficient balance.

### Transfer
Transfers funds securely between accounts.

### Statement Generation
Displays:
- Account Information
- Current Balance
- Recent Transactions

---

## 👥 Team Members

| Name | Enrollment |
|--------|------------|
| Muhammad Abu Bakar Farooq | 03-135232-039 |
| Muhammad Ahmad Fazal | 03-135232-042 |
| Hafiz Usama Khalil | 03-135232-021 |
| Muhammad Ali Tahir | 03-135232-048 |

---

## 👨‍🏫 Supervisor

**Mr. Hamza Waseem**

Bahria University Lahore Campus

---

## 📄 License

This project was developed for educational purposes as part of the Object-Oriented Programming Lab course at Bahria University Lahore Campus.
