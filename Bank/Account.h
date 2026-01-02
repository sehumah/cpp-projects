#include <string>

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    struct Owner {
        std::string first_name;
        std::string last_name;
        std::string full_name;
    };

public:
    Owner owner;
    std::string number;
    float balance = 0.0;
    Account(const std::string first_name, const std::string last_name, const std::string number);
    ~Account();
};

#endif  // ACCOUNT_H
