#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include "get_suppliers_command.hpp"
#include "input.hpp"

using namespace std;

get_suppliers_command::get_suppliers_command(supplier_manager& manager)
:
_manager(manager)
{}

void get_suppliers_command::execute()
{
    cout << "\n";

    unsigned int opt = 0;
    input::input_number(opt, 
        "Get suppliers by: product type - 0, product and min quantity - 1> ");
    
    try 
    {
        vector<supplier*> suppliers;
        if (opt == 0)
        {
            string product_type;
            cout << "Product type> ";
            getline(cin, product_type);

            suppliers = _manager.get_suppliers_by_product_type(product_type);
        }
        else if (opt == 1)
        {
            product_st prod;
            cout << "Product name> ";
            getline(cin, prod.product_name);

            cout << "Product type> ";
            getline(cin, prod.product_type);

            unsigned int min_quantity = 0;
            input::input_number(min_quantity, "Min quantity> ");

            unsigned int day_count = 0;
            input::input_number(day_count, "Day count> ");

            suppliers = _manager.get_suppliers_by_product_quantity(prod, min_quantity, day_count);
        }
        else 
        {
            cout << "Failed to get suppliers: invalid option\n";
            return;
        }

        cout << "-------------------------\n";
        cout << "SUPPLIER_COUNT: " << suppliers.size() << endl;
        cout << "-------------------------\n";

        for (unsigned int i = 0; i < suppliers.size(); ++i)
        {
            cout << "SUPPLIER_NAME_" << to_string(i + 1) << ": " << 
                suppliers[i]->get_name() << endl;
            cout << "-------------------------\n";
        }
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
