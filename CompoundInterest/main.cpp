#include <iostream>
#include <cmath>  // for std::pow()


int main () {
    std::cout << "==================================\n | Compound Interest Calculator |\n==================================\n\n";
    std::cout << "Calculate the compounding interest on your loan or investment using the formula, T = PA(1 + (roi/t))^ty, where:\n";
    std::cout << "T = total accrued amount, including interest\n";
    std::cout << "PA = principal amount\n";
    std::cout << "roi = the annual interest rate for the amount borrowed or deposited\n";
    std::cout << "t = the number of times the interest compounds yearly (compounding frequency)\n";
    std::cout << "y = the number of years the principal amount has been borrowed or deposited\n\n";
    std::cout << "Let's begin...\n\n";
    double T, PA, ir;
    int t, y, input;
    do {
        std::cout << "Enter the principal amount: ";
        std::cin >> PA;
        std::cout << "Enter the annual interest rate (%): ";
        std::cin >> ir;
        std::cout << "Enter the annual compounding frequency: ";
        std::cin >> t;
        std::cout << "Enter the number of years: ";
        std::cin >> y;

        T = PA * std::pow(1 + ((ir / 100) / t), (t * y));  // calculate the total
        std::cout << "\nThe total accrued amount, including interest will be: " << T << "\n\n";
        std::cout << "|--------------------|\n|        Menu        |\n|--------------------|\n";
        std::cout << "| 1. Calculate again |\n| 2. Exit            |\n|--------------------|\n Select 1 or 2: ";
        std::cin >> input;
        std::cout << '\n';
    } while (input == 1);
    return 0;
}
