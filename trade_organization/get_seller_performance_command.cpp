#include <iostream>
#include "get_seller_performance_command.hpp"
#include "util.hpp"
#include "input.hpp"

get_seller_performance_command::get_seller_performance_command(seller_manager& manager)
:
_manager(manager)
{}

void get_seller_performance_command::execute()
{
    cout << "\n";

    string seller_phone_number;
    cout << "Seller phone number xxx-xxx-xx-xx> ";
    getline(cin, seller_phone_number);

    if (!util::is_valid_phone_number(seller_phone_number))
    {
        cout << "Failed to get seller performance: seller phone number is not valid\n";
        return;
    }

    unsigned int opt = 0;
    input::input_number(opt, "0 - all trade points, 1 - by trade point type, 2 - by trade point name> ");

    try
    {
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
            cout << "Failed to get seller performance: invalid dates\n";
            return;
        }

        float performance = 0;
        if (opt == 0)
            performance = _manager.get_seller_performance(seller_phone_number, start, end);
        else if (opt == 1)
        {
            unsigned int opt_type = 0;
            input::input_number(opt_type, "Traid point type: KIOSK - 0, STORE - 1, DEPARTMENT_STORE - 2> ");
            
            string trade_point_type;
            if (opt_type == 0)
                trade_point_type = "KIOSK";
            if (opt_type == 1)
                trade_point_type = "STORE";
            else if (opt_type == 2)
                trade_point_type = "D_STORE";
            else
            {
                cout << "Failed to get seller performance: invalid option\n";
                return;
            }

            performance = _manager.get_seller_performance_by_tp_type(
                seller_phone_number, trade_point_type, start, end);
        }
        else if (opt == 2)
        {
            string trade_point_name;
            cout << "Trade point name> ";
            getline(cin, trade_point_name);

            performance = _manager.get_seller_performance_by_tp_name(
                seller_phone_number, trade_point_name, start, end);
        }
        else
        {
            cout << "Failed to get seller performance: invalid option\n";
            return;
        }

        seller* sel = _manager.get_seller_by_phone_number(seller_phone_number);
        cout << "-------------------------\n";
        cout << "SELLER_FIRST_NAME: " << sel->get_first_name() << endl;
        cout << "SELLER_MIDDLE_NAME: " << sel->get_middle_name() << endl;
        cout << "SELLER_LAST_NAME: " << sel->get_last_name() << endl;
        cout << "SELLER_PHONE_NUMBER: " << sel->get_phone_number() << endl;
        cout << "SALARY: " << sel->get_salary() << endl;
        cout << "PERFORMANCE: " << performance << endl;
        cout << "-------------------------\n";
    }
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
}
