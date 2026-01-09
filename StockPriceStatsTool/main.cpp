#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <cmath>


struct Statistics {
    float mean(const std::vector<float>& values) const {
        return values.empty() ? 0.0f : (std::accumulate(values.begin(), values.end(), 0.0f) / values.size());
    }

    float variance(const std::vector<float>& values) const {
        if (values.empty()) {
            return 0.0f;
        }
        const float avg = mean(values);  // find the mean
        float variance = 0.0f;
        
        // calculate squared deviations from the mean
        std::for_each(values.begin(), values.end(), [&](const float& value) { variance += std::powf((value - avg), 2); });
        return  variance / values.size();  // divide all summed squared deviations by N
    }

    float std_dev(const float& variance) const {
        return std::sqrtf(variance);
    }

    float std_dev(const std::vector<float>& values) const {
        return std::sqrtf(variance(values));
    }

    // Calculates SMA of the most recent N days
    float simple_moving_average(const std::vector<float>& prices, const int& period) const {
        if (period == 0 || period > prices.size()) {
            return 0.0f;
        }
        float sma = 0.0f;
        for (std::size_t i = 0; i < period; ++i) {
            sma += prices.at(i);
        }
        return (sma / period);
    }

    /**
     * TODO: Modify SMA function to accept end_index to enable 
     * calculating the SMA over N days end at end_index days prior.
     */
};



int main () {
    std::cout << "=================================\n | Stock Price Statistics Tool | \n=================================\n";
    std::cout << "This program reads a csv file of stock prices and calculates\nthe mean, variance, standard deviation and simple moving average.\n\n";
    std::cout << "Would you like to also compute the Simple Moving Average?\n1. Yes\n2. No\n\nEnter 1 or 2: ";
    int option, period;
    std::cin >> option;
    
    if (option == 1) {
        std::cout << "\nEnter the SMA period (no. of days): ";
        std::cin >> period;
    }

    std::vector<float> open_prices;
    std::vector<float> high_prices;
    std::vector<float> low_prices;
    std::vector<float> close_prices;

    open_prices.reserve(251);
    high_prices.reserve(251);
    low_prices.reserve(251);
    close_prices.reserve(251);

    // load csv file of 2025 AAPL stock prices for input/reading
    std::ifstream infile("2025_aapl_data.csv", std::ios::in);

    // read from the input file
    if (infile.is_open()) {
        std::string headers, row, token, volume;
        std::stringstream ss;
        std::vector<std::string> vector;
        vector.reserve(6);
        std::getline(infile, headers);
        while (std::getline(infile, row)) {
            volume.clear();  // clear the string, in preparation for the next line
            ss.str("");  // Clear the content of the stringstream
            ss.clear();  // Reset any error flags
            ss << row;   // Insert the row into the stringstream
            while (std::getline(ss, token, ',')) {
                if (token.find('/') != std::string::npos) {
                    vector.emplace_back(token);
                } else if ((token.front() == '"') && (token.back() == '"')) {
                    vector.emplace_back(token.substr(1, token.length()-2));
                } else {
                    volume.append(token);
                }
            }
            vector.emplace_back(volume);

            // save line data for later processing
            open_prices.emplace_back(std::stof(vector.at(1)));
            high_prices.emplace_back(std::stof(vector.at(2)));
            low_prices.emplace_back(std::stof(vector.at(3)));
            close_prices.emplace_back(std::stof(vector.at(4)));

            // clear the vector
            vector.clear();
        }
        infile.close();
    } else {
        std::cout << "Error opening file.\n";
    }


    // Perform calculations use the Statistics class
    Statistics statistics;

    float avg_open  = statistics.mean(open_prices);
    float avg_high  = statistics.mean(high_prices);
    float avg_low   = statistics.mean(low_prices);
    float avg_close = statistics.mean(close_prices);

    float var_open  = statistics.variance(open_prices);
    float var_high  = statistics.variance(high_prices);
    float var_low   = statistics.variance(low_prices);
    float var_close = statistics.variance(close_prices);

    float std_dev_open  = statistics.std_dev(var_open);
    float std_dev_high  = statistics.std_dev(var_high);
    float std_dev_low   = statistics.std_dev(var_low);
    float std_dev_close = statistics.std_dev(var_close);

    // Print values
    std::cout << "\n|==========================================================|\n";
    std::cout << "|          |    Open   |    High   |     Low   |   Close   |\n";
    std::cout << "|==========================================================|\n";
    std::printf("|     Mean |%11f|%11f|%11f|%11f|\n", avg_open, avg_high, avg_low, avg_close);
    std::cout << "|----------------------------------------------------------|\n";
    std::printf("| Variance |%11f|%11f|%11f|%11f|\n", var_open, var_high, var_low, var_close);
    std::cout << "|----------------------------------------------------------|\n";
    std::printf("| Std. Dev |%11f|%11f|%11f|%11f|\n", std_dev_open, std_dev_high, std_dev_low, std_dev_close);
    std::cout << "|==========================================================|\n\n";

    // calculate & display SMA
    if (option == 1 && period != 0) {
        std::cout << "The Simple Moving Average over a " << period << " day period is: " << statistics.simple_moving_average(close_prices, period) << ".\n\n";
    }
    return 0;
}
