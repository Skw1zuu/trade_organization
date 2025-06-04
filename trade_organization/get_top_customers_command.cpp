#include <exception>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "get_top_customers_command.hpp"
#include "input.hpp"
#include "customer.hpp"

get_top_customers_command::get_top_customers_command(customer_manager& manager)
:
_manager(manager)
{}

void get_top_customers_command::execute()
{
    cout << "\n";

    unsigned int opt = 0;
    input::input_number(opt, "0 - all trade points, 1 - by trade point type, 2 - by trade point name> ");

    try 
    {
        vector<pair<customer*, float>> stat;
        if (opt == 0)
            stat = _manager.get_top_active_customers();
        else if (opt == 1)
        {
            unsigned int opt_type = 0;
            input::input_number(opt_type, "Traid point type: STORE - 0, DEPARTMENT_STORE - 1> ");
            
            std::string trade_point_type;
            if (opt_type == 0)
                trade_point_type = "STORE";
            else if (opt_type == 1)
                trade_point_type = "D_STORE";
            else
            {
                cout << "Failed to get top customers: invalid option\n";
                return;
            }

            stat = _manager.get_top_active_customers_by_tp_type(trade_point_type);
        }
        else if (opt == 2)
        {
            string trade_point_name;
            cout << "Trade point name> ";
            getline(cin, trade_point_name);

            stat = _manager.get_top_active_customers_by_tp_name(trade_point_name);
        }
        else
        {
            cout << "Failed to get top customers: invalid option\n";
            return;
        }

        for (unsigned int i = 0; i < stat.size(); ++i)
        {
            cout << "-------------------------\n";
            cout << "TOP: " << to_string(i + 1) << endl;
            cout << "CUSTOMER_NAME: " << stat[i].first->get_name() << endl;
            cout << "CUSTOMER_PHONE_NUMBER: " << stat[i].first->get_phone_number() << endl;
            cout << "PURCHASE_AMOUNT: " << stat[i].second << endl;
        }
        cout << "-------------------------\n";
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
