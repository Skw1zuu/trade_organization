#include <iostream>
#include <vector>
#include "add_supplier_command.hpp"
#include "product_order.hpp"
#include "util.hpp"

add_supplier_command::add_supplier_command(supplier_manager& manager)
:
_manager(manager)
{}

void add_supplier_command::execute()
{
    cout << "\n";

    string name;
    cout << "Supplier name> ";
    getline(cin, name);

    try 
    {
        vector<product_order_st> orders = util::get_product_orders_ui();
        _manager.create_supplier(name, orders);
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }

}
