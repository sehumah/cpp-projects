#include "Account.h"
#include <map>

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
    void checkLoanStatus(std::string& acc_num);
    void printAccounts();

private:
    long double m_reserves = 3132426987.23;
    std::map<std::string, Account> m_accounts;
    int generateAccNum();
};

#endif  // BANK_H
