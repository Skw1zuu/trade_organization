#include <exception>
#include <iostream>
#include <vector>
#include "get_turnover_command.hpp"
#include "input.hpp"

get_turnover_command::get_turnover_command(sale_manager& manager)
:
_manager(manager)
{}

void get_turnover_command::execute()
{
    cout << "\n";

    unsigned int trade_point_count = 0;
    input::input_number(trade_point_count, "Trade point count> ");

    if (trade_point_count == 0)
    {
        cout << "Failed to get turnover: trade point count should be > 0\n";
        return;
    }

    vector<string> trade_point_names;
    string trade_point_name;
    for (unsigned int i = 0; i < trade_point_count; ++i)
    {
        cout << "Trade point name " << to_string(i + 1) << "> ";
        getline(cin, trade_point_name);
        trade_point_names.push_back(trade_point_name);
    }

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
            cout << "Failed to get turnover: invalid dates\n";
            return;
        }

        cout << "-------------------------\n";
        cout << "TURNOVER: " << _manager.get_tp_turnover(trade_point_names, start, end) << endl;
        cout << "-------------------------\n";
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }

}
