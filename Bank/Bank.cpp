#include "Bank.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <random>

Bank::Bank () {
    // read a text file (accounts.txt) containing a CSV of each account's details.
    // std::ifstream accounts_file("accounts.txt");
}

Bank::~Bank () {}

void Bank::openAccount() {
    std::cout << "\nWe're glad you want to conduct banking with us.\nPlease fill the following details to create your new C++ Bank account:\n";
    std::string fname, lname;
    std::cout << "\nEnter your first name: ";
    std::cin >> fname;
    std::cout << "Enter your last name: ";
    std::cin >> lname;
    std::cout << "\nPlease hold on, your account is being created...\n";
    
    // create an account & add it to the accounts map
    std::string acc_num = std::to_string(Bank::generateAccNum());
    Bank::m_accounts.insert({acc_num, Account(fname, lname, acc_num)});
    // Bank::m_accounts[acc_num] = Account(fname, lname, acc_num);
    
    // create a file (if not exists) to add the new account to the accounts (file)
    std::this_thread::sleep_for(std::chrono::seconds(3));  // simulate time elapsing
    std::cout << "Account successfully created!\n\nA new C++ Bank account has been created for " << fname << ' ' << lname << ".\nYour account number is " << acc_num << ".\nYou can now start banking with your C++ Bank account.\n";
}

void Bank::closeAccount() {
    // ask user to enter their account number
    std::string acc_num;
    std::cout << "We're sorry to see you go!\nPlease enter your account number: ";
    std::cin >> acc_num;
    if (m_accounts.contains(acc_num)) {
        std::cout << "Closing account " << m_accounts.find(acc_num)->first << " for " << m_accounts.find(acc_num)->second.owner.full_name << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        m_accounts.erase(acc_num);
        std::cout << "Account closed successfully!\n";
    } else {
        std::cout << "No account found for account number " << acc_num << ".\nPlease correct the account number and try again.\n";
    }
}

void Bank::depositMoney() {
    std::string acc_num;
    float amount;
    // customer enters their account number
    std::cout << "\nEnter your account number: ";
    std::cin >> acc_num;

    // use their account number to find their account in the accounts map
    if (m_accounts.contains(acc_num)) {
        // if found, ask for the deposit amount & update their account balance
        std::cout << "Enter the deposit amount: ";
        std::cin >> amount;

        std::cout << "\nPlease hold on while we update your account balance...\n";
        m_accounts.find(acc_num)->second.balance += amount;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Success! You new account balance is: " << m_accounts.find(acc_num)->second.balance <<  ".\n";
    } else {
        std::cout << "\nThere's no account with the account number: " << acc_num << ".\nPlease check the account number and try again.\n";
    }
}

void Bank::withdrawMoney() {
    // get their account number
    std::string acc_num;
    float amount;
    std::cout << "Enter your account number: ";
    std::cin >> acc_num;
    std::cout << "Enter the amount you'd like to withdraw: ";
    std::cin >> amount;

    // find the account and make the withdrawal
    if (m_accounts.contains(acc_num) && (amount < m_accounts.find(acc_num)->second.balance)) {
        std::cout << "\nPlease wait...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        m_accounts.find(acc_num)->second.balance -= amount;
        std::cout << "Withdrawal complete! Your new account balance is: " << m_accounts.find(acc_num)->second.balance << ".\n";
    } else {
        std::cout << "\nAn error occured...Either you don't have enough in your account to make a withdrawal\nor there's no account with the account number: " << acc_num << ".\nPlease check the details and try again.\n";
    }
}

void Bank::transferMoney() {
    std::string source_acc, dest_acc;
    float amount;

    // get the source account number
    std::cout << "\nEnter the source account number: ";
    std::cin >> source_acc;
    std::cout << "Enter amount to transfer: ";
    std::cin >> amount;
    std::cout << "Enter the destination account number: ";
    std::cin >> dest_acc;

    // execute transfer if all inputs are valid
    if (m_accounts.contains(source_acc) && (amount < m_accounts.find(source_acc)->second.balance) && m_accounts.contains(dest_acc)) {
        std::cout << "\nTransfering " << amount << " from " << m_accounts.find(source_acc)->second.owner.full_name << "'s account (" << source_acc << ") to " << m_accounts.find(dest_acc)->second.owner.full_name << "'s account (" << dest_acc << ")...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        m_accounts.find(source_acc)->second.balance -= amount;
        m_accounts.find(dest_acc)->second.balance += amount;
        std::cout << "Transfer complete!\nSource account balance: " << m_accounts.find(source_acc)->second.balance << "\nDestination account balance: " << m_accounts.find(dest_acc)->second.balance << ".\n";
    } else {
        std::cout << "\nAn error occured...Either the source or destination account number is wrong, or\nthere's not enough balance in the source account to conduct this transaction.\nPlease check the details and try again.\n";
    }
}

void Bank::checkLoanStatus(std::string& account_number) {}

void Bank::printAccounts() {
    std::cout << "\nPrinting all accounts at The C++ Bank...\n";
    
    std::cout << "|==================================================|\n";
    std::cout << "| Account Owner | Account Number | Account Balance |\n";
    std::cout << "|==================================================|\n";
    for (std::map<std::string, Account>::iterator it = m_accounts.begin(); it != m_accounts.end(); ++it) {
        std::printf("|%15s|%16s|%17f|\n", it->second.owner.full_name.c_str(), it->first.c_str(), it->second.balance);
    }
    /*
    for (const auto&[acc_num, account] : m_accounts) {
        std::printf("|%15s|%16s|%17f|\n", account.owner.full_name.c_str(), acc_num.c_str(), account.balance);
    }
    */
    std::cout << "|==================================================|\nDone printing.\n";    
}


int Bank::generateAccNum() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1111, 9999);
    return dist(rng);
}
