#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "OrderBook.h"


/**
 * An orderbook is a list of buy & sell orders of a particular financial instrument (stocks, bonds, ETFs, commodities or cryptocurrencies).
 * 
 * Types of Orders in an OrderBook:
 * --------------------------------
 * 1. Market orders: These orders are executed immediately at the best available price. 
 *    For example, if a buyer submits a market order, it will be matched with the lowest ask price in the order book.
 *    It doesn't care about the transaction price as long as it's the best price.
 * 
 * 2. Limit orders: A limit order allows traders to specify the price at which they are willing to buy or sell.
 *    This order will only execute if the market price reaches the trader's limit price, ensuring control over 
 *      the execution price but with no guarantee that the trade will be executed.
 * 
 * 3. Stop orders: These are conditional orders placed to buy or sell an asset once its price moves past a 
 *      specified point, triggering a market or limit order.
 *      Stop orders are often used to minimize losses, making them very useful for risk management.
 * 
 *    Stop Orders: Also known as a ‘stop-loss’ order, this is an order to buy or sell a stock once the 
 *     price reaches a specific trigger point, intending to limit an investor’s potential loss. 
 *     This order becomes a market order once the stop price is met or exceeded.
 * 
 * Other order types include All-or-None, Fill-or-Kill, and Immediate-on-Cancel 
 * 
 * Buy orders (bids): show what buyers are ready to pay. Usually listed from highest to the lowest bid price.
 * Sell orders (asks): show what sellers want to get for their assets. They’re listed from the lowest to the highest ask price.
 * 
 * 
 * The bid-ask spread is the difference between the highest price a buyer is willing to pay for an 
 * asset (bid price) and the lowest price at which a seller is willing to sell the same asset (ask price). 
 * In other words, it’s the cost of entering or exiting a trade. 
 */



int main() {
    std::cout << "\n========================\n  C++ LIMIT ORDER BOOK\n========================\n";
    OrderBook orderbook;
    int option;

    do {
        std::cout << "\n|--------------------|\n|        MENU        |\n|--------------------|\n| 1. Place an order  |\n| 2. View order book |\n|--------------------|\n\nSelect an option: ";
        std::cin >> option;
        
        switch (option) {
            case 1:
                std::cout << "\n-----------------\n| Placing Order |\n-----------------\n| 1. BUY order  |\n| 2. SELL order |\n-----------------\nSelect order type: ";
                int side, price, quantity;
                std::cin >> side;
                std::cout << "\nEnter order price: ";
                std::cin >> price;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                if (side == 1 || side == 2) {
                    // get timepoint at the moment & convert it to time_t
                    std::time_t timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

                    // pass a now_t pointer to std::ctime & create a hash to generate unique ID for the order
                    std::size_t id = std::hash<std::string>{}(std::ctime(&timestamp));

                    // add the order to the orders
                    orderbook.add_order({id, price, quantity, (side == 1 ? Side::buy : Side::sell), timestamp});

                    // create Order object and add it to the orders
                    // Order order{id, price, quantity, (side == 1 ? Side::buy : Side::sell), timestamp};
                    // orderbook.add_order(order);
                }
                break;
            case 2:
                orderbook.print_orderbook();
                break;
            default:
                break;
        }
    } while(option == 1 || option == 2);

    std::cout << std::endl;
    return 0;
}