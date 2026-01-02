#include <iostream>
#include "Bank.h"


int main() {
    std::cout << "======================\n ||| The C++ Bank |||\n======================\n\n";
    // std::cout << "Herzlich Wilkommen bei The C++ Bank!\nPlease login or sign up below to access our services:\n\n";
    // std::cout << "1. Login\n2. Sign up\n3. Quit\n\nSelect an option: ";
    std::cout << "Welcome to The C++ Bank. What would you like to do today?\n";

    // create a Bank object
    Bank bank;

    int option;
    do {
        // print menu & take input
        std::cout <<"\n|======================|\n";
        std::cout <<"| 1. Open an account   |\n";
        std::cout <<"| 2. Deposit money     |\n";
        std::cout <<"| 3. Withdraw money    |\n";
        std::cout <<"| 4. Transfer money    |\n";
        // std::cout <<"| 5. Get a loan        |\n";
        std::cout <<"| 6. View all accounts |\n";
        // std::cout <<"| 7. Close an account  |\n";
        std::cout <<"| 8. Exit              |\n";
        std::cout <<"|======================|\n";
        std::cout <<"\nSelect an option: ";
        std::cin >> option;
        
        // act on user's input
        switch (option) {
            case 1:  // account creation
                bank.openAccount();
                break;
            case 2:  // deposit
                bank.depositMoney();
                break;
            case 3:  // withdrawal
                bank.withdrawMoney();
                break;
            case 4:  // transaction
                bank.transferMoney();
                break;
            case 5:  // loan
                break;
            case 6:  // view all accounts
                bank.printAccounts();
                break;
            case 7:  // account termination
                break;
            case 8:  // exit
                std::cout << "Goodbye! Have a nice day.\n";
                exit(0);
                break;
            default:
                std::cout << "Invalid input. Goodbye!\n";
                exit(-1);
                break;
        }
    } while (option != 8);
    return 0;
}

/**
 * Improvements:
 * - customers should login to their accounts before they can withdraw, deposit, transact or get a loan.
 * - Make it multi-threaded to simulate multiple tellers who need to access the bank's vault to check how
 *   much the bank has in reserves to confirm if a loan is possible.
 */
