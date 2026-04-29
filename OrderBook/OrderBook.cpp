#include <ctime>
#include <random>
#include <string>
#include <chrono>
#include <iostream>
#include "OrderBook.h"


/// PRIVATE ///
template <typename Map>
void OrderBook::add_to_side(Map &container, int &side, int &price, int &quantity) {
    auto [price_level_it, _] = container.try_emplace(price, PriceLevel(price));
    price_level_it->second.orders.emplace_back(++order_id, price, quantity, static_cast<Side>(side), std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    auto order_it = std::prev(price_level_it->second.orders.end());
    order_lookup_table.try_emplace(order_id, price, price_level_it, order_it);
    // order_lookup_table[order_id] = {price, price_level_it, order_it};
}


const int OrderBook::generate_int(const int &a, const int &b) const {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> int_distribution(a, b);
    return int_distribution(rng);
}

const int OrderBook::generate_price() const {
    return generate_int(200, 210);
}

const int OrderBook::generate_quantity() const {
    return generate_int(100, 200);
}



/// PUBLIC ///
OrderBook::OrderBook() {
    /*
    // add bids
    int bids_count = 5;
    for(int i=0; i < bids_count; ++i) {
        std::time_t timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::size_t id = std::hash<std::string>{}(std::ctime(&timestamp));
        add_order({id, generate_price(), generate_quantity(), Side::buy, timestamp});
    }
    
    // add asks
    int asks_count = 7;
    for(int i=0; i < asks_count; ++i) {
        std::time_t timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::size_t id = std::hash<std::string>{}(std::ctime(&timestamp));
        add_order({id, generate_price(), generate_quantity(), Side::sell, timestamp});
    }
    */
}


//
OrderBook::~OrderBook() {}


//
const int OrderBook::add_order(int &side, int &price, int &quantity) {
    if (side == 1) {
        add_to_side(bids, side, price, quantity);
    } else {
        add_to_side(asks, side, price, quantity);
    }
    return order_id;
}


//
const bool OrderBook::cancel_order(int &id) {
    auto it = order_lookup_table.find(id);  // find order via ID
    if (it == order_lookup_table.end()) {  // return if order doesn't exist
        return false;
    } else {
        OrderLocation &order_location = it->second;
        Side side = order_location.order_it->side;
        order_location.price_level_it->second.orders.erase(order_location.order_it);  // remove order from price level
        if (order_location.price_level_it->second.orders.empty()) {  // if price level becomes empty, remove it from the map
            if (side == Side::buy) {
                bids.erase(order_location.price_level_it);
            } else {
                asks.erase(order_location.price_level_it);
            }
        }
        order_lookup_table.erase(id);  // remove order from lookup table
        return true;
    }
}


// uses the order ID to modify the order's quantity
const bool OrderBook::modify_order(int &id, int &quantity) {
    auto it = order_lookup_table.find(id);
    if (it == order_lookup_table.end()) {
        return false;
    } else {  // order exists
        // get the order from the lookup table, change its quantity & return success
        OrderLocation &order_location = it->second;
        order_location.order_it->quantity = quantity;
        return true;
    }
}


const bool OrderBook::has_order(int &id) const {
    return order_lookup_table.contains(id);
}


const Order OrderBook::get_order(int &id) const {
    return *(order_lookup_table.at(id).order_it);
}


//
const int OrderBook::best_bid() const {
    if(bids.empty()) {
        return 0;
    }
    return bids.cbegin()->first;
}


//
const int OrderBook::best_ask() const {
    if(asks.empty()) {
        return 0;
    }
    return asks.cbegin()->first;
}


//
const int OrderBook::bid_ask_spread() const {
    return (best_ask() - best_bid());
}


// handle partial fills
// make performance optimizations


//
void OrderBook::print_bids() const {
    std::cout << "\nBids:\n-----\n";
    // for(std::map<int, PriceLevel, std::greater<int>>::const_iterator it = bids.cbegin(); it != bids.cend(); ++it) {}
    for(const auto& [price, price_level]: bids) {
        std::cout << "[" << price << "] = " << price_level.orders.size() << (price_level.orders.size() == 1 ? " bid\n" : " bids\n");
    }
}


//
void OrderBook::print_asks() const {
    std::cout << "\nAsks:\n-----\n";
    // for(std::map<int, PriceLevel, std::less<int>>::const_iterator it = asks.cbegin(); it != asks.cend(); ++it) {}
    for(const auto& [price, price_level]: asks) {
        std::cout << "[" << price << "] = " << price_level.orders.size() << (price_level.orders.size() == 1 ? " ask\n" : " asks\n");
    }
}


//
void OrderBook::print_lookup_table() const {
    std::cout << "\nOrder Lookup Table:\n-------------------\n";
    // for (std::unordered_map<int, OrderLocation>::const_iterator it = order_lookup_table.cbegin(); it != order_lookup_table.cend(); it++) {}
    for (const auto& [id, order_location] : order_lookup_table) {
        std::cout << "[" << id << "] = " << order_location.price << '\n';
    }
}


//
void OrderBook::print_orderbook() const {
    print_asks();
    std::cout << "\n";
    print_bids();
    std::cout << "\n";
    print_lookup_table();
}