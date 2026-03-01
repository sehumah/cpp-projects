#include <string>

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    struct Owner {
        std::string first_name;
        std::string last_name;
        const std::string full_name () const {
            return first_name + ' ' + last_name;
        }
    };

public:
    Owner owner;
    std::string number;
    double balance;
    double loan;
    Account(const std::string first_name, const std::string last_name, const std::string number);
    ~Account();
    void reset();
};

#endif  // ACCOUNT_H
