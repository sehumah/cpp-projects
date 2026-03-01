#include "Bank.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <utility>
#include <fstream>
#include <sstream>
#include <iomanip>


// for random number generation
std::random_device rd;
std::mt19937 rng(rd());


Bank::Bank () {
    // fill the bank's reserves with an arbitrary number
    std::uniform_real_distribution<double> res_dist(10'000'000, 100'000'000);
    Bank::m_reserves = res_dist(rng);

    // read accounts data from csv file and populate the accounts map
    std::ifstream infile("accounts.csv", std::ios::in);
    if (infile.is_open()) {
        std::string headers, row, token;
        std::stringstream ss;
        std::vector<std::string> account_data;
        account_data.reserve(5);

        // 1st read the headers
        std::getline(infile, headers);

        // 2nd - read data from each line of the file
        while (std::getline(infile, row)) {
            ss.str("");  // clear the content of the stringstream
            ss.clear();  // reset any error flags
            ss << row;  // insert data from the line into the stringstream

            // 3rd - save tokens from the line
            while (std::getline(ss, token, ',')) {
                account_data.emplace_back(token);
            }

            // create Account object with data from the vector
            Account account = Account(account_data.at(0), account_data.at(1), account_data.at(2));
            account.balance = std::stod(account_data.at(3));
            account.loan = std::stod(account_data.at(4));

            // insert the account object into the m_accounts map
            Bank::m_accounts.emplace(std::make_pair(account.number, account));

            // reset the account object & clear the vector
            account.reset();
            account_data.clear();
        }
    }

    // close the file
    infile.close();
}


Bank::~Bank () {
    // write data from the Bank's accounts map to the csv file and close it
    std::ofstream outfile("accounts.csv", std::ios::out);
    if (outfile.is_open()) {
        // 1st - write the headers
        outfile << "first_name,last_name,account_number,balance,loan\n";

        // 2nd - now loop through the accounts and write each account's data to the file
        for (auto it = Bank::m_accounts.cbegin(); it != Bank::m_accounts.cend(); it++) {
            outfile << it->second.owner.first_name << ',' << it->second.owner.last_name << ',' <<  it->second.number << ',' << std::fixed << std::setprecision(6) << it->second.balance << ',' << std::fixed << std::setprecision(6) << it->second.loan << '\n';
        }
    }

    // close the file
    outfile.close();
}


////////// generate random numbers //////////
std::uniform_int_distribution<int> i_dist(1111, 9999);
int Bank::generateAccNum() {
    return i_dist(rng);
}

std::uniform_real_distribution<double> d_dist(5.0, 14.0);
double Bank::getInterestRate() {
    return d_dist(rng);
}
////////// END //////////


void Bank::openAccount() {
    std::cout << "\nWe're glad you want to conduct banking with us.\nPlease fill the following details to create your new C++ Bank account:\n";
    std::string fname, lname, acc_num;
    std::cout << "\nEnter your first name: ";
    std::cin >> fname;
    std::cout << "Enter your last name: ";
    std::cin >> lname;
    std::cout << "\nPlease hold on, your account is being created...\n";

    // create an account & add it to the accounts map
    do {
        acc_num = std::to_string(Bank::generateAccNum());
    } while (Bank::m_accounts.contains(acc_num));

    std::this_thread::sleep_for(std::chrono::seconds(3));  // simulate time elapsing
    Bank::m_accounts.emplace(std::make_pair(acc_num, Account(fname, lname, acc_num)));
    // Bank::m_accounts.insert({acc_num, Account(fname, lname, acc_num)});
    // Bank::m_accounts[acc_num] = Account(fname, lname, acc_num);

    // create a file (if not exists) to add the new account to the accounts (file)
    std::cout << "Account successfully created!\n\nA new C++ Bank account has been created for " << fname << ' ' << lname << ".\nYour account number is " << acc_num << ".\nYou can now start banking with your C++ Bank account.\n";
}


void Bank::closeAccount() {
    // ask user to enter their account number
    std::string acc_num;
    std::cout << "\nWe're sorry to see you go!\n\nPlease enter your account number: ";
    std::cin >> acc_num;
    if (Bank::m_accounts.contains(acc_num)) {  //  && (Bank::m_accounts.find(acc_num)->second.loan <= 0.0) - prevents them from closing an account if they owe outstanding loans
        std::map<std::string, Account>::const_iterator account = Bank::m_accounts.find(acc_num);
        std::cout << "\nClosing account " << account->first << " for " << account->second.owner.full_name() << "...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        Bank::m_accounts.erase(acc_num);
        std::cout << "Account closed successfully!\n";
    } else {
        std::cout << "No account found for account number " << acc_num << ".\nPlease correct the account number and try again.\n";
    }
}


void Bank::depositMoney() {
    std::string acc_num;
    double amount;
    // customer enters their account number
    std::cout << "\nEnter your account number: ";
    std::cin >> acc_num;
    std::cout << "Enter the deposit amount: ";
    std::cin >> amount;

    // if found, ask for the deposit amount & update their account balance
    if (Bank::m_accounts.contains(acc_num) && (amount > 0)) {
        std::cout << "\nPlease hold on while we update your account balance...\n";
        auto account = Bank::m_accounts.find(acc_num);
        account->second.balance += amount;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "Success! You new account balance is: " << std::fixed << std::setprecision(6) << account->second.balance <<  ".\n";
    } else {
        std::cout << "\nAn error occurred. Either the account doesn't exists or the deposit amount is invalid.\n";
    }
}


void Bank::withdrawMoney() {
    // get their account number
    std::string acc_num;
    double amount;
    std::cout << "\nEnter your account number: ";
    std::cin >> acc_num;
    std::cout << "Enter amount to withdraw: ";
    std::cin >> amount;

    // find the account and make the withdrawal
    if (Bank::m_accounts.contains(acc_num) && (amount > 0) && (amount <= Bank::m_accounts.find(acc_num)->second.balance)) {
        std::cout << "\nPlease wait...\n";
        auto account = Bank::m_accounts.find(acc_num);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        account->second.balance -= amount;
        std::cout << "Withdrawal complete! Your new account balance is: " << std::fixed << std::setprecision(6) << account->second.balance << ".\n";
    } else {
        std::cout << "\nAn error occured...Either you don't have enough in your account to make a withdrawal\nor there's no account with the account number: " << acc_num << ".\nPlease check the details and try again.\n";
    }
}


void Bank::transferMoney() {
    std::string source_acc, dest_acc;
    double amount;

    // get the source account number
    std::cout << "\nEnter the source account number: ";
    std::cin >> source_acc;
    std::cout << "Enter the destination account number: ";
    std::cin >> dest_acc;
    std::cout << "Enter amount to transfer: ";
    std::cin >> amount;

    // execute transfer if all inputs are valid & transfer is possible
    if (Bank::m_accounts.contains(source_acc) && Bank::m_accounts.contains(dest_acc) && (amount <= Bank::m_accounts.find(source_acc)->second.balance)) {
        auto source = Bank::m_accounts.find(source_acc);
        auto destination = Bank::m_accounts.find(dest_acc);
        std::cout << "\nTransfering " << amount << " from " << source->second.owner.full_name() << "'s account (" << source_acc << ") to " << destination->second.owner.full_name() << "'s account (" << dest_acc << ")...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        source->second.balance -= amount;
        destination->second.balance += amount;
        std::cout << "Transfer complete!\nSource account balance: " << std::fixed << std::setprecision(6) << source->second.balance << "\nDestination account balance: " << std::fixed << std::setprecision(6) << destination->second.balance << ".\n";
    } else {
        std::cout << "\nAn error occured...Either the source or destination account number is wrong, or\nthere's not enough balance in the source account to conduct this transaction.\nPlease check the details and try again.\n";
    }
}


void Bank::getLoan() {
    std::string acc_num;
    double loan_amt;
    std::cout << "\nEnter your account number: ";
    std::cin >> acc_num;
    std::cout << "Enter loan amount: ";
    std::cin >> loan_amt;

    if (Bank::m_accounts.contains(acc_num) && (loan_amt < Bank::m_reserves)) {
        std::cout << "\nProcessing loan... please wait...\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto account = Bank::m_accounts.find(acc_num);
        Bank::m_reserves -= loan_amt;
        double interest_rate = getInterestRate();
        account->second.balance += loan_amt;
        double total_loan_amount = (loan_amt + (loan_amt * (interest_rate / 100)));
        account->second.loan += total_loan_amount;
        std::cout << "\nLoan amount of " << loan_amt << " has been approved for you with a " << interest_rate << "\% interest rate.\nYou will be paying a total of " << total_loan_amount << " in return.";
        std::cout << "\nYour new account balance is: " << std::fixed << std::setprecision(6) << account->second.balance << ".\nYour total loan owed to the bank is: " << std::fixed << std::setprecision(6) << account->second.loan << ".\nYou may withdraw your new loan.\n";
    } else {
        std::cout << "\nAn error occured...Either the account number is invalid or\nthe loan amount is greater than what the bank can offer.\n";
        // std::cout << "\nWe unfortunately cannot provide you with a loan of " << loan_amt << " at this time.\n";
    }
}


void Bank::printAccounts() {
    std::cout << "\nPrinting all accounts at The C++ Bank...\n";
    
    std::cout << "|=====================================================================|\n";
    std::cout << "| Account Owner | Account Number | Account Balance | Outstanding Loan |\n";
    std::cout << "|=====================================================================|\n";
    for (std::map<std::string, Account>::const_iterator it = Bank::m_accounts.cbegin(); it != Bank::m_accounts.cend(); ++it) {
        std::printf("|%15s|%16s|%17f|%18f|\n", it->second.owner.full_name().c_str(), it->first.c_str(), it->second.balance, it->second.loan);
    }
    /*
    for (const auto& [acc_num, account] : Bank::m_accounts) {
        std::printf("|%15s|%16s|%17f|%18f|\n", account.owner.full_name().c_str(), acc_num.c_str(), account.balance, account.loan);
    }
    */
    std::cout << "|=====================================================================|\nDone printing.\n";    
}