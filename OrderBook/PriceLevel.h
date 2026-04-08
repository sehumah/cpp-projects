#pragma once

#include <list>
#include "Order.h"


struct PriceLevel {
    int price;
    std::list<Order> orders;

    PriceLevel(int p): price(std::move(p)) {}
};