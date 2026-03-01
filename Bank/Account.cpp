#include "Account.h"
#include <utility>


Account::Account(const std::string first_name, const std::string last_name, const std::string number): number(std::move(number)) {
    owner.first_name = std::move(first_name);
    owner.last_name = std::move(last_name);
    balance = 0.0;
    loan = 0.0;
}

Account::~Account() {}


void Account::reset() {
    Account::owner.first_name = "";
    Account::owner.last_name = "";
    Account::number = "";
    Account::balance = 0.0;
    Account::loan = 0.0;
}
