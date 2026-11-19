# Bank Management System (C++)

A console-based **Bank Management System** in C++ with two portals:
- **Admin Portal**: Add, view, update, and delete client accounts.
- **Client ATM Portal**: Log in, check balance, deposit money, and withdraw funds safely.

## Features
- Dynamic client list using `std::vector` and structured data using `struct` and `enum`.
- 6-digit random account number generation (`rand` + `srand`).
- Login attempt limit (up to 3 tries) for both admin and client.
- Balance validation before withdrawal and positive amount checks.
- Input buffer cleaning (`cin.ignore`) before `getline`.

## Compile and Run
```bash
g++ -std=c++17 main.cpp -o bank_system
./bank_system
