#include <exception>
#include <iostream>
#include <utility>
#include <vector>
#include "get_prices_command.hpp"
#include "input.hpp"

get_prices_command::get_prices_command(trade_point_manager& manager)
:
_manager(manager)
{}

void get_prices_command::execute()
{
    cout << "\n";

    product_st prod;
    cout << "Product name> ";
    getline(cin, prod.product_name);

    cout << "Product type> ";
    getline(cin, prod.product_type);

    unsigned int opt = 0;
    input::input_number(opt, "0 - all trade points, 1 - by trade point type, 2 - by trade point name> ");

    try 
    {
        vector<pair<trade_point*, product_order_st>> stat;
        if (opt == 0)
            stat = _manager.get_orders_by_product(prod);
        else if (opt == 1)
        {
            unsigned int opt_type = 0;
            input::input_number(opt_type, "Traid point type: KIOSK - 0, STORE - 1, DEPARTMENT_STORE - 2> ");
            
            string trade_point_type;
            if (opt_type == 0)
                trade_point_type = "KIOSK";
            if (opt_type == 1)
                trade_point_type = "STORE";
            else if (opt_type == 2)
                trade_point_type = "D_STORE";
            else
            {
                cout << "Failed to get prices: invalid option\n";
                return;
            }

            stat = _manager.get_orders_by_product_and_tp_type(prod, trade_point_type);
        }
        else if (opt == 2)
        {
            string trade_point_name;
            cout << "Trade point name> ";
            getline(cin, trade_point_name);

            stat.push_back(_manager.get_order_by_product_and_tp_name(prod, trade_point_name));
        }
        else
        {
            cout << "Failed to get prices: invalid option\n";
            return;
        }

        for (unsigned int i = 0; i < stat.size(); ++i)
        {
            cout << "-------------------------\n";
            cout << "TRADE_POINT_NAME: " << stat[i].first->get_name() << endl;
            cout << "TRADE_POINT_TYPE: " << stat[i].first->get_type() << endl;
            cout << "PRODUCT_NAME: " << stat[i].second.product_name << endl;
            cout << "PRODUCT_TYPE: " << stat[i].second.product_type << endl;
            cout << "QUANTITY: " << stat[i].second.quantity << endl;
            cout << "PRICE_PER_UNIT: " << stat[i].second.price_per_unit << endl;
        }
        cout << "-------------------------\n";
    }
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
