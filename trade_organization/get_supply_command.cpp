#include <exception>
#include <iostream>
#include <vector>
#include "get_supply_command.hpp"

get_supply_command::get_supply_command(supply_manager& manager)
:
_manager(manager)
{}

void get_supply_command::execute()
{
    cout << "\n";

    string supplier_name;
    cout << "Supplier name> ";
    getline(cin, supplier_name);

    try 
    {
        string start_date;
        cout << "Start date DD-MM-YYYY (skip if not required)> ";
        getline(cin, start_date);

        vector<supply_st> sups;
        if (start_date != "")
        {
            date start(start_date);
            string end_date;
            cout << "End date DD-MM-YYYY> ";
            getline(cin, end_date);
            date end(end_date);

            if (!(start < end))
            {
                cout << "Failed to get supply: invalid dates\n";
                return;
            }

            sups = _manager.get_supply_by_supplier(supplier_name, start, end);
        }
        else 
            sups = _manager.get_supply_by_supplier(supplier_name);

        cout << "-------------------------\n";
        cout << "SUPPLY_COUNT: " << sups.size() << endl;
        cout << "-------------------------\n";

        for (unsigned int i = 0; i < sups.size(); ++i)
        {
            cout << "SUPPLY_NUMBER: " << sups[i].supply_number << endl;
            cout << "SUPPLY_COOPERATION_START: " << sups[i].cooperation_start.to_string() << endl;
            cout << "SUPPLY_COOPERATION_END: " << sups[i].cooperation_end.to_string() << endl;
            cout << "ORDER_COUNT: " << sups[i].orders.size() << endl;
            cout << "-------------------------\n";

            for (unsigned int j = 0; j < sups[i].orders.size(); ++j)
            {
                cout << "\tPRODUCT_NAME: " << sups[i].orders[j].product_name << endl;
                cout << "\tPRODUCT_TYPE: " << sups[i].orders[j].product_type << endl;
                cout << "\tQUANTITY: " << sups[i].orders[j].quantity << endl;
                cout << "\tPRICE_PER_UNIT: " << sups[i].orders[j].price_per_unit << endl;
                cout << "-------------------------\n";
            }
        }
    } 
    catch (exception& ex) 
    {
        cout << ex.what();
    }
}
