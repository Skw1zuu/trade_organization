#include <exception>
#include <iostream>
#include <vector>
#include "get_salaries_command.hpp"
#include "input.hpp"

get_salaries_command::get_salaries_command(seller_manager& manager)
:
_manager(manager)
{}

void get_salaries_command::execute()
{
    cout << "\n";

    unsigned int opt = 0;
    input::input_number(opt, "0 - all trade points, 1 - by trade point type, 2 - by trade point name> ");

    try 
    {
        vector<seller*> sellers;
        if (opt == 0)
            sellers = _manager.get_sellers();
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
                cout << "Failed to get salaries: invalid option\n";
                return;
            }

            sellers = _manager.get_sellers_by_tp_type(trade_point_type);
        }
        else if (opt == 2)
        {
            string trade_point_name;
            cout << "Trade point name> ";
            getline(cin, trade_point_name);

            sellers = _manager.get_sellers_by_tp_name(trade_point_name);
        }
        else 
        {
            cout << "Failed to get salaries: invalid option\n";
            return;
        }

        for (unsigned int i = 0; i < sellers.size(); ++i)
        {
            cout << "-------------------------\n";
            cout << "SELLER_FIRST_NAME: " << sellers[i]->get_first_name() << endl;
            cout << "SELLER_MIDDLE_NAME: " << sellers[i]->get_middle_name() << endl;
            cout << "SELLER_LAST_NAME: " << sellers[i]->get_last_name() << endl;
            cout << "SELLER_PHONE_NUMBER: " << sellers[i]->get_phone_number() << endl;
            cout << "SALARY: " << sellers[i]->get_salary() << endl;
        }
        cout << "-------------------------\n";
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
