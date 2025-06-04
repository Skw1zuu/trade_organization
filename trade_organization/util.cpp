#include <iostream>
#include <stdexcept>
#include <regex>
#include "util.hpp"
#include "input.hpp"

vector<product_order_st> util::get_product_orders_ui()
{
    unsigned int order_count = 0;
    input::input_number(order_count, "Order count> ");

    if (order_count == 0)
        throw runtime_error("Failed to get order count: order count shuld be > 0\n");

    vector<product_order_st> orders;
    product_order_st order;
    for (unsigned int i = 0; i < order_count; ++i)
    {
        cout << "Order-" << to_string(i + 1) << " product name> ";
        getline(cin, order.product_name);
    
        cout << "Order-" << to_string(i + 1) << " product type> ";
        getline(cin, order.product_type);

        input::input_number(order.quantity, "Order-" + to_string(i + 1) + " quantity> ");
        input::input_number(order.price_per_unit, "Order-" + to_string(i + 1) + " price per unit> ");

        orders.push_back(order);
    }

    return orders;
}

bool util::is_valid_phone_number(const string& phone_number) // xxx-xxx-xx-xx
{
    regex pattern(R"(\d{3}-\d{3}-\d{2}-\d{2})");
    return regex_match(phone_number, pattern);
}
