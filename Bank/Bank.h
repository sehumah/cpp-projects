#include "Account.h"
#include <map>
#include <random>

#ifndef BANK_H
#define BANK_H

class Bank {        
public:
    Bank();
    ~Bank();
    void openAccount();
    void closeAccount();
    void depositMoney();
    void withdrawMoney();
    void transferMoney();
    void getLoan();
    void printAccounts();

private:
    long double m_reserves;
    std::map<std::string, Account> m_accounts;
    int generateAccNum();
    double getInterestRate();
};

#endif  // BANK_H
