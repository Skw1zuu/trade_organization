#include <exception>
#include <iostream>
#include <vector>
#include "add_sale_command.hpp"
#include "product_order.hpp"
#include "util.hpp"
#include "input.hpp"

add_sale_command::add_sale_command(sale_manager& manager)
:
_manager(manager)
{}

void add_sale_command::execute()
{
    cout << "\n";

    string trade_point_name;
    cout << "Trade point name> ";
    getline(cin, trade_point_name);

    string seller_phone_number;
    cout << "Seller phone number xxx-xxx-xx-xx> ";
    getline(cin, seller_phone_number);

    if (!util::is_valid_phone_number(seller_phone_number))
    {
        cout << "Failed to add sale: seller phone number is not valid\n";
        return;
    }

    string customer_name;
    cout << "Customer name (skip if trade point type is KIOSK)> ";
    getline(cin, customer_name);

    string customer_phone_number;
    cout << "Customer phone number (skip if trade point type is KIOSK)> ";
    getline(cin, customer_phone_number);

    if (!util::is_valid_phone_number(customer_phone_number) && customer_phone_number != "")
    {
        cout << "Failed to add sale: customer phone number is not valid\n";
        return;
    }

    try 
    {
        string sale_date;
        cout << "Sale date> ";
        getline(cin, sale_date);
        date dat(sale_date);

        unsigned int order_count = 0;
        input::input_number(order_count, "Order count> ");

        if (order_count == 0)
        {
            cout << "Failed to add sale: order count should be > 0\n";
            return;
        }

        vector<product_order_quantity_st> orders;
        product_order_quantity_st order;
        for (unsigned int i = 0; i < order_count; ++i)
        {
            cout << "Order-" << to_string(i + 1) << " product name> ";
            getline(cin, order.product_name);
    
            cout << "Order-" << to_string(i + 1) << " product type> ";
            getline(cin, order.product_type);

            input::input_number(order.quantity, "Order-" + to_string(i + 1) + " quantity> ");

            orders.push_back(order);
        }

        _manager.create_sale(dat, orders, customer_name, 
            customer_phone_number, seller_phone_number, trade_point_name);
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
