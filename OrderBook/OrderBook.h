#pragma once

#include <unordered_map>
#include "OrderLocation.h"


class OrderBook {
private:
    std::map<int, PriceLevel, std::greater<int>> bids;
    std::map<int, PriceLevel, std::less<int>> asks;
    std::unordered_map<int, OrderLocation> order_lookup_table;
    int order_id = 0;
    const int generate_int(const int &a, const int &b) const;
    const int generate_price() const;
    const int generate_quantity() const;

    template <typename Map>
    void add_to_side(Map &container, int &side, int &price, int &quantity);

public:
    OrderBook();
    ~OrderBook();
    const int add_order(int &side, int &price, int &quantity);
    const bool cancel_order(int &id);
    const bool modify_order(int &id, int &quantity);
    const bool has_order(int &id) const;
    const Order get_order(int &id) const;
    const int best_bid() const;
    const int best_ask() const;
    const int bid_ask_spread() const;
    void print_bids() const;
    void print_asks() const;
    void print_lookup_table() const;
    void print_orderbook() const;
};