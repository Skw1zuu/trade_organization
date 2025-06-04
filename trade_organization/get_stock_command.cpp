#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "get_stock_command.hpp"

get_stock_command::get_stock_command(trade_point_manager& manager)
:
_manager(manager)
{}

void get_stock_command::execute()
{
    cout << "\n";

    string trade_point_name;
    cout << "Trade point name> ";
    getline(cin, trade_point_name);

    try 
    {
        vector<product_order_st> orders = _manager.get_stock_by_tp_name(trade_point_name);

        for (unsigned int i = 0; i < orders.size(); ++i)
        {
            cout << "-------------------------\n";
            cout << "PRODUCT_NAME: " << orders[i].product_name << endl;
            cout << "PRODUCT_TYPE: " << orders[i].product_type << endl;
            cout << "QUANTITY: " << orders[i].quantity << endl;
            cout << "PRICE_PER_UNIT: " << orders[i].price_per_unit << endl;
        }
        cout << "-------------------------\n";
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
