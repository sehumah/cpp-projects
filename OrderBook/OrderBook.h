#pragma once

#include <map>
#include <random>
#include <string>
#include <chrono>
#include <ctime>
#include <unordered_map>
#include <algorithm>
#include "PriceLevel.h"


struct OrderBook {
    private:
        std::map<int, PriceLevel, std::greater<int>> bids;
        std::map<int, PriceLevel, std::less<int>> asks;
        std::unordered_map<int, Order> order_lookup_table;
        int order_id = 1;
        
        /*  Helper Functions  */
        const int generate_int(const int& a, const int& b) {
            std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<int> int_distribution(a, b);
            return int_distribution(rng);
        }

        const int generate_price() {
            return generate_int(200, 210);
        }

        const int generate_quantity() {
            return generate_int(100, 200);
        }


    public:
        OrderBook() {
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
        
        ~OrderBook() {}


        //
        const int add_order(int &side, int &price, int &quantity) {
            // std::time_t timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            // Order order {order_id++, price, quantity, static_cast<Side>(side), timestamp};
            Order order {order_id++, price, quantity, static_cast<Side>(side), std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};

            switch(order.side) {
                case Side::buy:
                    if(!bids.contains(order.price)) {
                        bids.emplace(order.price, PriceLevel(order.price));
                    }
                    bids.at(order.price).orders.emplace_back(order);
                    break;
                case Side::sell:
                    if(!asks.contains(order.price)) {
                        asks.emplace(order.price, PriceLevel(order.price));
                    }
                    asks.at(order.price).orders.emplace_back(order);
                    break;
                default:
                    break;
            }

            /*
            switch(static_cast<Side>(side)) {
                case Side::buy:
                    auto [price_level_it, inserted] = bids.try_emplace(price, PriceLevel(price));
                    price_level_it->second.orders.emplace_back(order_id++, price, quantity, static_cast<Side>(side), std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
                    auto order_it = std::prev(price_level_it->second.orders.cend());
                    break;
                case Side::sell:
                    auto [price_level_it, _] = asks.try_emplace(price, PriceLevel(price));
                    price_level_it->second.orders.emplace_back(order_id++, price, quantity, static_cast<Side>(side), std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
                    std::list<Order>::iterator order_it = std::prev(price_level_it->second.orders.end());
                    // save order iterator in the lookup
                    // order_lookup_table.emplace(order_it->id, order_it);
                    break;
                default:
                    break;
            }
            */
            order_lookup_table.emplace(order.id, order);
            return order.id;
        }


        const bool cancel_order(int& id) {  // cancel and remove order
            // check if the order exists
            if (order_lookup_table.contains(id)) {
                // get the order & remove it from the appropriate list
                auto order = order_lookup_table.at(id);
                std::size_t removed_order;
                switch (order.side) {
                    case Side::buy:
                        // remove order from price level
                        removed_order = bids.at(order.price).orders.remove_if([&order](Order& o){ return o.id == order.id; });
                        
                        // remove price level if it becomes empty
                        if (bids.at(order.price).orders.empty()) {
                            bids.erase(order.price);
                        }
                        break;
                    case Side::sell:
                        // remove order from price level
                        removed_order = asks.at(order.price).orders.remove_if([&order](Order& o){ return o.id == order.id; });

                        // remove price level if it becomes empty
                        if (asks.at(order.price).orders.empty()) {
                            asks.erase(order.price);
                        }
                        break;
                }

                // now remove order from lookup table
                order_lookup_table.erase(order.id);
                return true;
            }
            return false;
        }


        // uses the order ID to modify the order's price or quantity
        const bool modify_order(int& id, int& quantity) {
            // get the order from the lookup table
            Order order = order_lookup_table.at(id);

            // get the order's side, find it from the appropriate map:list, change the order's quantity & return success/failure
            if(order.side == Side::buy) {
                auto& buy_orders = bids.at(order.price).orders;
                auto it = std::find_if(buy_orders.begin(), buy_orders.end(), [&order](const Order& o) { return o.id == order.id; });
                if(it != buy_orders.end()) {
                    it->quantity = quantity;
                    return true;
                }
            } else if(order.side == Side::sell) {
                auto& sell_orders = asks.at(order.price).orders;
                auto it = std::find_if(sell_orders.begin(), sell_orders.end(), [&order](const Order& o) { return o.id == order.id; });
                if(it != sell_orders.end()) {
                    it->quantity = quantity;
                    return true;
                }
            }
            return false;
        }

        const bool has_order(int& id) const {
            return order_lookup_table.contains(id);
        }

        const Order get_order(int& id) const {
            return order_lookup_table.at(id);
        }


        // 
        const int best_bid() const {
            if(bids.empty()) {
                return 0;
            }
            return bids.cbegin()->first;
        }


        // 
        const int best_ask() const {
            if(asks.empty()) {
                return 0;
            }
            return asks.cbegin()->first;
        }


        // 
        const int bid_ask_spread() const {
            return (best_ask() - best_bid());
        }


        // handle partial fills
        // make performance optimizations


        // 
        void print_bids() const {
            std::cout << "\nBids:\n-----\n";
            // for(std::map<int, PriceLevel, std::greater<int>>::const_iterator it = bids.cbegin(); it != bids.cend(); ++it) {}
            for(const auto& [price, price_level]: bids) {
                std::cout << "[" << price << "] = " << price_level.orders.size() << (price_level.orders.size() == 1 ? " bid\n" : " bids\n");
            }
        }


        // 
        void print_asks() const {
            std::cout << "\nAsks:\n-----\n";
            // for(std::map<int, PriceLevel, std::less<int>>::const_iterator it = asks.cbegin(); it != asks.cend(); ++it) {}
            for(const auto& [price, price_level]: asks) {
                std::cout << "[" << price << "] = " << price_level.orders.size() << (price_level.orders.size() == 1 ? " ask\n" : " asks\n");
            }
        }


        // 
        void print_orderbook() const {
            print_asks();
            std::cout << "\n";
            print_bids();
        }
};