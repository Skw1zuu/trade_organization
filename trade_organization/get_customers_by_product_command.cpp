#include <exception>
#include <iostream>
#include <vector>
#include "get_customers_by_product_command.hpp"
#include "input.hpp"

using namespace std;

get_customers_by_product_command::get_customers_by_product_command(customer_manager& manager)
:
_manager(manager)
{}

void get_customers_by_product_command::execute()
{
    cout << "\n";

    unsigned int opt = 0;
    input::input_number(opt, "Customers by: product type and period - 0, product and quantity - 1> ");

    try
    {
        vector<customer*> customers;
        if (opt == 0)
        {
            string product_type;
            cout << "Product type> ";
            getline(cin, product_type);

            string start_date;
            cout << "Start date DD-MM-YYYY> ";
            getline(cin, start_date);
            date start(start_date);

            string end_date;
            cout << "End date DD-MM-YYYY> ";
            getline(cin, end_date);
            date end(end_date);

            if (!(start < end))
            {
                cout << "Feiled to get customers by product: invalid dates\n";
                return;
            }

            customers = _manager.get_customers_by_purchase(product_type, start, end);
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

            customers = _manager.get_customers_by_purchase(prod, min_quantity);
        }
        else 
        {
            cout << "Feiled to get customers by product: invalid option\n";
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
