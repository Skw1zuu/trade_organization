#include <exception>
#include <iostream>
#include <vector>
#include "add_supply_command.hpp"
#include "date.hpp"
#include "product.hpp"
#include "input.hpp"

add_supply_command::add_supply_command(supply_manager& manager)
:
_manager(manager)
{}

void add_supply_command::execute()
{
    cout << "\n";

    string name;
    cout << "Supplier name> ";
    getline(cin, name);

    try
    {
        string cooperation_start;
        cout << "Cooperation start date DD-MM-YYYY> ";
        getline(cin, cooperation_start);
        date start(cooperation_start);

        string cooperation_end;
        cout << "Cooperation end date DD-MM-YYYY> ";
        getline(cin, cooperation_end);
        date end(cooperation_end);

        if (start < end)
        {
            unsigned int product_count = 0;
            input::input_number(product_count, "Product count> ");

            if (product_count == 0)
            {
                cout << "Failed to add supply: product count shuld be > 0\n";
                return;
            }

            vector<product_st> products;
            product_st prod;
            for (unsigned int i = 0; i < product_count; ++i)
            {
                cout << "Order-" << to_string(i + 1) << " product name> ";
                getline(cin, prod.product_name);

                cout << "Order-" << to_string(i + 1) << " product type> ";
                getline(cin, prod.product_type);

                products.push_back(prod);
            }

            _manager.create_supply(name, start, end, products);
        }
        else
        {
            cout << "Failed to add supply: invalid dates\n";
            return;
        }
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
