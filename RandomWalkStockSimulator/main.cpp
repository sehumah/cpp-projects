#include <iostream>
#include <fstream>
#include <sstream>
#include <random>


/**
 * This project simulates a stock price path using random numbers
 */

int main () {
    std::cout << "=================================\n | Random Walk Stock Simulator | \n=================================\n\n";

    double high = 0.0;
    double low = 1000.0;
    std::vector<std::string> dates;
    dates.reserve(251);
    std::vector<double> prices;
    prices.reserve(251);
    int num_lines = 0;

    // Read and parse a CSV file of stock prices
    std::ifstream file("2025_aapl_data.csv", std::ios::in);
    if (file.is_open()) {
        std::string headers, line, token;
        std::stringstream ss;
        std::vector<double> values;
        values.reserve(4);
        
        // read & process daily stock data
        std::getline(file, headers);
        while (std::getline(file, line)) {
            values.clear();
            ss.str("");
            ss.clear();
            ss << line;
            while (std::getline(ss, token, ',')) {
                if (token.find('/') != std::string::npos) {
                    dates.emplace_back(token);
                }
                else if (token.front() == '"' && token.back() == '"') {  // token is either a (open, high, low, close) value
                    values.emplace_back(std::stod(token.substr(1, token.length()-2)));
                }
            }
            // update the high & low variables
            high = std::max(high, values.at(1));
            low = std::min(low, values.at(2));

            // i counts number of lines in the file
            num_lines++;
        }
    } else {
        std::cerr << "Error opening input file." << std::endl;
    }

    // close the file
    file.close();

    // Use the low & high prices as the bounds for uniform_real_distribution
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> random_doubles(low, high);

    // Generate random stock prices within the defined range
    while (num_lines > 0) {
        prices.emplace_back(random_doubles(rng));
        num_lines--;
    }

    std::cout << "Bounds: (" << low << ", " << high << ")\n\n";

    // print simulated stock prices over time
    for (std::size_t i = 0; i < dates.size() && i < prices.size(); i++) {
        std::printf("%10s : %5f\n", dates.at(i).c_str(), prices.at(i));
    }

    return 0;
}
