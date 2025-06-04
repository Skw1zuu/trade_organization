#pragma once
#include <vector>
#include "product_order.hpp"

using namespace std;

class util
{
public:
    static vector<product_order_st> get_product_orders_ui();
    static bool is_valid_phone_number(const string& phone_number); // xxx-xxx-xx-xx

};
