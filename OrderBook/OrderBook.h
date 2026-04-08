#pragma once

#include <map>
#include <random>
#include "PriceLevel.h"


struct OrderBook {
    private:
        std::map<int, PriceLevel, std::greater<int>> bids;
        std::map<int, PriceLevel, std::less<int>> asks;
        std::random_device rd;
        
        /*  Helper Functions  */
        const int generate_int(const int& a, const int& b) {
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
        void add_order(const Order& order) {
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
        }


        /*
        void cancel_order(Order order) {  // cancel and remove order
            switch (order.side) {
                case Side::buy:
                    if (bids.contains(order.price)) {
                        // auto orders = bids.at(order.price).orders;
                        // find the order by id
                        std::list<Order>::const_iterator it = std::find(bids.at(order.price).orders.cbegin(), bids.at(order.price).orders.cend(), order.id);
                        
                        // use the iterator to remove the order from the list
                        bids.at(order.price).orders.erase(it);
                    }
                    break;
                case Side::sell:
                    if (asks.contains(order.price)) {
                        auto orders = asks.at(order.price).orders;
                        std::list<Order>::const_iterator it = std::find(orders.cbegin(), orders.cend(), order.price);
                        orders.erase(it);
                    }
                    break;
                default:
                    break;
            }
        }
        */


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
            for(const auto&[price, price_level]: bids) {
                if(price_level.orders.size() > 1) {
                    std::cout << "[" << price << "] = " << price_level.orders.size() << " bids\n";
                } else {
                    std::cout << "[" << price << "] = " << price_level.orders.size() << " bid\n";
                }
            }
        }


        // 
        void print_asks() const {
            std::cout << "\nAsks:\n-----\n";
            // for(std::map<int, PriceLevel, std::less<int>>::const_iterator it = asks.cbegin(); it != asks.cend(); ++it) {}
            for(const auto&[price, price_level]: asks) {
                if(price_level.orders.size() > 1) {
                    std::cout << "[" << price << "] = " << price_level.orders.size() << " asks\n";
                } else {
                    std::cout << "[" << price << "] = " << price_level.orders.size() << " ask\n";
                }
            }
        }


        // 
        void print_orderbook() const {
            print_asks();
            // std::cout << "\n--------------------\n";
            std::cout << "\n";
            print_bids();
        }
};