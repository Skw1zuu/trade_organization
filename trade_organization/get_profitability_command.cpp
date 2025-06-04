#include <exception>
#include <iostream>
#include "get_profitability_command.hpp"
#include "trade_point.hpp"

get_profitability_command::get_profitability_command(trade_point_manager& manager)
:
_manager(manager)
{}

void get_profitability_command::execute()
{
    cout << "\n";

    string trade_point_name;
    cout << "Trade point name> ";
    getline(cin, trade_point_name);

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

        float profitability = 0;
        if (start < end)
            profitability = _manager.get_tp_profitability(trade_point_name, start, end);
        else 
        {
            cout << "Failed to get profitability: invalid dates\n";
            return;
        }

        trade_point* tp = _manager.get_trade_point_by_name(trade_point_name);

        cout << "-------------------------\n";
        cout << "TRADE_POINT_NAME: " << trade_point_name << endl;
        cout << "TRADE_POINT_TYPE: " << tp->get_type() << endl;
        cout << "TRADE_POINT_AREA: " << tp->get_area() << endl;
        cout << "TRADE_POINT_TOTAL_COUNTERS: " << tp->get_total_counters() << endl;
        cout << "TRADE_POINT_RENT: " << tp->get_rent() << endl;
        cout << "TRADE_POINT_UTILITIES: " << tp->get_utilities() << endl;
        cout << "PROFITABILITY: " << profitability << endl;
        cout << "-------------------------\n";
    } 
    catch (exception& ex)
    {
        cout << ex.what() << endl;
    }
}
