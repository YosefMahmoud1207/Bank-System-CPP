# Bank System in C++ 🚀

A robust, console-based Banking System application developed in modern C++. This project demonstrates strong software engineering principles, utilizing Object-Oriented Programming (OOP) and File Handling to manage secure user accounts, transactions, and persistent data storage.

## Key Features & Architecture 🛠️

* **Object-Oriented Programming (OOP):** 
  * Implements an abstract base class `Account` with derived classes `CurrentAccount` and `SavingAccount` to handle account-specific rules, withdrawal fees, and investment balances using polymorphism.
* **Security & Authentication:** 
  * Features a custom cryptographic hashing implementation (`HashingStrInput`) using the FNV-1a hash algorithm to securely handle passwords.
  * Robust input validation for National IDs (14 digits) and strict password policies (minimum 8 characters with uppercase, lowercase, numbers, and special characters).
  * Account lockout mechanism after multiple failed login attempts with password recovery options.
* **Persistent File Handling:** 
  * Automatically saves and loads user profiles (`account.txt`) and transaction histories (`Transactions.txt`) safely across sessions.
  * Dynamic account number generation and sequence recovery from persistent storage.
* **Comprehensive Banking Operations:** 
  * Secure deposit, withdrawal, fund transfers between accounts with balance validation, and detailed transaction history logs.

## Project Structure 📁

```text
Bank-System-CPP/
│
├── HeaderFiles/
│   ├── Account.h
│   ├── BankSystem.h
│   ├── BankUtils.h
│   ├── CurrentAccount.h
│   └── SavingAccount.h
│
├── ImplementFiles/
│   ├── Account.cpp
│   ├── BankSystem.cpp
│   ├── BankUtils.cpp
│   ├── CurrentAccount.cpp
│   └── SavingAccount.cpp
│
├── FileHandling/
│   ├── account.txt
│   └── Transactions.txt
│
├── BANKSYSTEM.cpp
└── .gitignore


## How to Compile and Run 💻

* **1. Clone the repository:**
git clone [https://github.com/YosefMahmoud1207/Bank-System-CPP.git](https://github.com/YosefMahmoud1207/Bank-System-CPP.git)

* **2. Compile all source files:**
g++ -IHeaderFiles ImplementFiles/*.cpp BANKSYSTEM.cpp -o Account.exe

* **3. Run the executable:**
./Account.exe
