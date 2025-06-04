#include <exception>
#include <iostream>
#include <utility>
#include <vector>
#include "get_sales_efficiency_command.hpp"
#include "input.hpp"

get_sales_efficiency_command::get_sales_efficiency_command(trade_point_manager& manager)
:
_manager(manager)
{}

void get_sales_efficiency_command::execute()
{
    cout << "\n";

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
        cout << "Failed to get sales efficiency: invalid option\n";
        return;
    }

    unsigned int opt = 0;
    input::input_number(opt, "Efficiency by: area - 0, halls - 1, counters - 2> ");

    try 
    {
        vector<pair<trade_point*, float>> stat;
        if (opt == 0)
            stat = _manager.get_area_amount_relation(trade_point_type);
        else if (opt == 1)
            stat = _manager.get_hall_amount_relation(trade_point_type);
        else if (opt == 2)
            stat = _manager.get_counters_amount_relation(trade_point_type);
        else
        {
            cout << "Failed to get sales efficiency: invalid option\n";
            return;
        }

        for (unsigned int i = 0; i < stat.size(); ++i)
        {
            cout << "-------------------------\n";
            cout << "TRADE_POINT_NAME: " << stat[i].first->get_name() << endl;
            cout << "TRADE_POINT_TYPE: " << stat[i].first->get_type() << endl;
            cout << "EFFICIENCY: " << stat[i].second << endl;
        }
        cout << "-------------------------\n";
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
