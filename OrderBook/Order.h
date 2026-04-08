#pragma once

#include "enums.h"


struct Order {
    std::size_t id;  // hash value of the order's timestamp
    int price;
    int quantity;
    Side side;
    std::time_t timestamp;
    // type: market or limit
};