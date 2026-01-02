#include "Account.h"
#include <utility>

Account::Account(const std::string first_name, const std::string last_name, const std::string number): number(std::move(number)) {
    owner.first_name = std::move(first_name);
    owner.last_name = std::move(last_name);
    owner.full_name = owner.first_name + ' ' + owner.last_name;

    // read accounts.csv file & write the contents of the new account to it
}


Account::~Account() {}
