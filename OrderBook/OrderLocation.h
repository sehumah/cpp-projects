#pragma once

#include <map>
#include "PriceLevel.h"


struct OrderLocation {
    int price;
    std::map<int, PriceLevel>::iterator price_level_it;
    std::list<Order>::iterator order_it;
};