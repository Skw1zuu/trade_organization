#include <exception>
#include <iostream>
#include "get_supply_by_number_command.hpp"
#include "input.hpp"

get_supply_by_number_command::get_supply_by_number_command(supply_manager& manager)
:
_manager(manager)
{}

void get_supply_by_number_command::execute()
{
    cout << "\n";

    unsigned int supply_number = 0;
    input::input_number(supply_number, "Supply number> ");

    try 
    {
        supply_st sup = _manager.get_supply_by_number(supply_number);

        cout << "-------------------------\n";
        cout << "SUPPLY_NUMBER: " << sup.supply_number << endl;
        cout << "SUPPLY_COOPERATION_START: " << sup.cooperation_start.to_string() << endl;
        cout << "SUPPLY_COOPERATION_END: " << sup.cooperation_end.to_string() << endl;
        cout << "ORDER_COUNT: " << sup.orders.size() << endl;
        cout << "-------------------------\n";

        for (unsigned int i = 0; i < sup.orders.size(); ++i)
        {
            cout << "PRODUCT_NAME: " << sup.orders[i].product_name << endl;
            cout << "PRODUCT_TYPE: " << sup.orders[i].product_type << endl;
            cout << "QUANTITY: " << sup.orders[i].quantity << endl;
            cout << "PRICE_PER_UNIT: " << sup.orders[i].price_per_unit << endl;
            cout << "-------------------------\n";
        }
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
