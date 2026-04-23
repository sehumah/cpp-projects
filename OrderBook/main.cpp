#include <iostream>
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
    std::cout << "\n==========================\n   C++ LIMIT ORDER BOOK\n==========================";
    OrderBook orderbook;
    int option, side, price, quantity, orderID;

    do {
        std::cout << "\n|------------------------|\n|          MENU          |\n|------------------------|\n| 1. View order book     |\n| 2. Place an order      |\n| 3. Modify an order     |\n| 4. Cancel an order     |\n| 5. Execute order       |\n| 6. Get best ask        |\n| 7. Get best bid        |\n| 8. View bid-ask spread |\n| 0. Exit program        |\n|------------------------|\n\nSelect an option: ";
        std::cin >> option;
        switch (option) {
            case 1:  // VIEW ORDER BOOK
                orderbook.print_orderbook();
                break;
            case 2:  // PLACE AN ORDER
                std::cout << "\n-----------------\n| Placing Order |\n-----------------\n| 1. BUY order  |\n| 2. SELL order |\n-----------------\nSelect order type: ";
                std::cin >> side;
                std::cout << "\nEnter order price: ";
                std::cin >> price;
                std::cout << "Enter quantity: ";
                std::cin >> quantity;

                if (side == 1 || side == 2) {
                    int result = orderbook.add_order(side, price, quantity);
                    std::cout << "\nA new " << (side == 1 ? "BUY" : "SELL") << " order has been added.\nOrder id is: " << result << ".\n";
                }
                break;
            case 3:  // MODIFY AN ORDER
                std::cout << "\n-------------------\n| Modifying Order |\n-------------------\nYou can only modify an order's quantity.\n\nEnter order ID to proceed: ";
                std::cin >> orderID;
                // TODO: has_order should be a private method that shouldn't be accessible outside the orderbook class
                if (orderbook.has_order(orderID)) {
                    Order order = orderbook.get_order(orderID);
                    std::cout << "\nThe " << (order.side == Side::buy ? "BUY" : "SELL") << " order with id (" << order.id << ") has a quantity of " << order.quantity << ".\nEnter the new quantity: ";
                    std::cin >> quantity;
                    if (quantity > 0) {
                        if (orderbook.modify_order(orderID, quantity)) {
                            std::cout << "\nOrder with ID (" << order.id << ") successfully modified.\n";
                        } else {
                            std::cout << "\nOrder modification unsuccessful.\n";
                        }
                    }
                } else {
                    std::cout << "\nNo order with ID (" << orderID << ") found.\n";
                }
                break;
            case 4:  // CANCEL AN ORDER
                std::cout << "\n-------------------\n| Canceling Order |\n-------------------\n\nEnter order ID to proceed: ";
                std::cin >> orderID;
                if (orderbook.cancel_order(orderID)) {
                    std::cout << "\nOrder with ID (" << orderID << ") successfully cancelled.\n";
                } else {
                    std::cout << "\nNo order with ID (" << orderID << ") exists.\n";
                }
                break;
            case 5:  // EXECUTE ORDER
                break;
            case 6:  // BEST ASK
                std::cout << "\n------------\n| Best Ask |\n------------\n";
                std::cout << "Best ask: " << orderbook.best_ask() << '\n';
                break;
            case 7:  // BEST BID
                std::cout << "\n------------\n| Best Bid |\n------------\n";
                std::cout << "Best bid: " << orderbook.best_bid() << '\n';
                break;
            case 8:  // BID-ASK SPREAD
                std::cout << "\n------------------\n| Bid-Ask Spread |\n------------------\n";
                break;
            case 0:
                std::cout << "\nGoodbye!\n\n";
                std::exit(EXIT_SUCCESS);
                break;
            default:
                break;
        }
    } while(option != 0);

    std::cout << std::endl;
    return 0;
}