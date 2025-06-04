#include <exception>
#include <iostream>
#include "get_sales_command.hpp"
#include "input.hpp"

get_sales_command::get_sales_command(sale_manager& manager)
:
_manager(manager)
{}

void get_sales_command::execute()
{
    cout << "\n";

    product_st prod;
    cout << "Product name> ";
    getline(cin, prod.product_name);

    cout << "Product type> ";
    getline(cin, prod.product_type);

    try 
    {
        string start_date;
        cout << "Cooperation start date DD-MM-YYYY> ";
        getline(cin, start_date);
        date start(start_date);

        string end_date;
        cout << "Cooperation end date DD-MM-YYYY> ";
        getline(cin, end_date);
        date end(end_date);

        if (!(start < end))
        {
            cout << "Failed to get sales: invalid dates\n";
            return;
        }

        unsigned int opt = 0;
        input::input_number(opt, "0 - all trade points, 1 - by trade point type, 2 - by trade point name> ");

        unsigned int amount = 0;
        if (opt == 0)
            amount = _manager.get_sale_amount_by_product(prod, start, end);
        else if (opt == 1)
        {
            unsigned int opt_type = 0;
            input::input_number(opt_type, "Traid point type: KIOSK - 0, STORE - 1, DEPARTMENT_STORE - 2> ");
            
            string trade_point_type;
            if (opt_type == 0)
                trade_point_type = "KIOSK";
            else if (opt_type == 1)
                trade_point_type = "STORE";
            else if (opt_type == 2)
                trade_point_type = "D_STORE";
            else
            {
                cout << "Failed to get sales: invalid option\n";
                return;
            }

            amount = _manager.get_sale_amount_by_product_and_tp_type(prod, 
                trade_point_type, start, end);
        }
        else if (opt == 2)
        {
            string trade_point_name;
            cout << "Trade point name> ";
            getline(cin, trade_point_name);

            amount = _manager.get_sale_amount_by_product_and_tp_name(prod, 
                trade_point_name, start, end);
        }
        else 
        {
            cout << "Failed to get sales: invalid option\n";
            return;
        }

        cout << "-------------------------\n";
        cout << "PRODUCT_NAME: " << prod.product_name << endl;
        cout << "PRODUCT_TYPE: " << prod.product_type << endl;
        cout << "SALE_AMOUNT: " << amount << endl;
        cout << "-------------------------\n";
    } 
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
}
