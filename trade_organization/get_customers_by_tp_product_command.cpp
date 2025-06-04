#include <exception>
#include <iostream>
#include <vector>
#include "get_customers_by_tp_product_command.hpp"
#include "input.hpp"

get_customers_by_tp_product_command::get_customers_by_tp_product_command(
    customer_manager& manager)
:
_manager(manager)
{}

void get_customers_by_tp_product_command::execute()
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
        string start_date;
        cout << "Start date DD-MM-YYYY (skip if not required)> ";
        getline(cin, start_date);
        
        date start("00-00-0000");
        date end("99-99-9999");
        if (start_date != "")
        {
            start = date(start_date);

            string end_date;
            cout << "End date DD-MM-YYYY> ";
            getline(cin, end_date);
            
            end = date(end_date);

            if (!(start < end))
            {
                cout << "Feiled to get customers by tp product: invalid dates\n";
                return;
            }
        }

        vector<customer*> customers;
        if (opt == 0)
            customers = _manager.get_customers_by_product(prod, start, end);
        else if (opt == 1)
        {
            unsigned int opt_type = 0;
            input::input_number(opt_type, "Traid point type: STORE - 0, DEPARTMENT_STORE - 1> ");
            
            string trade_point_type;
            if (opt_type == 0)
                trade_point_type = "STORE";
            else if (opt_type == 1)
                trade_point_type = "D_STORE";
            else
            {
                cout << "Failed to get customers by tp product: invalid option\n";
                return;
            }

            customers = _manager.get_customers_by_product_and_tp_type(prod, 
                trade_point_type, start, end);
        }
        else if (opt == 2)
        {
            string trade_point_name;
            cout << "Trade point name> ";
            getline(cin, trade_point_name);

            customers = _manager.get_customers_by_product_and_tp_name(prod, 
                trade_point_name, start, end);
        }
        else 
        {
            cout << "Failed to get customers by tp product: invalid option\n";
            return;
        }

        cout << "-------------------------\n";
        cout << "CUSTOMER_COUNT: " << customers.size() << endl;
        cout << "-------------------------\n";

        for (unsigned int i = 0; i < customers.size(); ++i)
        {
            cout << "CUSTOMER_NAME: " << customers[i]->get_name() << endl;
            cout << "CUSTOMER_PHONE_NUMBER: " << customers[i]->get_phone_number() << endl;
            cout << "-------------------------\n";
        }
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
