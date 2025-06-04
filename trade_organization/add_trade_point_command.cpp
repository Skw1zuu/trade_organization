#include <exception>
#include <iostream>
#include <vector>
#include "add_trade_point_command.hpp"
#include "input.hpp"
#include "product_order.hpp"
#include "util.hpp"

add_trade_point_command::add_trade_point_command(trade_point_manager& manager)
:
_manager(manager)
{}

void add_trade_point_command::execute()
{
    cout << "\n";

    unsigned int opt = 0;
    input::input_number(opt, "Traid point type: KIOSK - 0, STORE - 1, DEPARTMENT_STORE - 2> ");

    if (opt > 2)
    {
        cout << "Failed to add trade point: invalid trade point type option\n";
        return;
    }

    string name;
    cout << "Trade point name> ";
    getline(cin, name);

    float area = 0;
    input::input_number(area, "Area> ");

    float rent = 0;
    input::input_number(rent, "Rent> ");

    float utilities = 0;
    input::input_number(utilities, "Utilities> ");

    unsigned int total_counters = 0;
    input::input_number(total_counters, "Total counters> ");

    try 
    {
        vector<product_order_st> orders = util::get_product_orders_ui();

        if (opt == 0)
        {
            _manager.create_kiosk(name, area, rent, utilities, total_counters, 
                orders);
            return;
        }
        
        unsigned int total_halls = 0;
        input::input_number(total_halls, "Total halls> ");

        if (total_halls == 0)
        {
            cout << "Failed to add trade point: total halls should be > 0\n";
            return;
        }

        if (opt == 1)
        {
            _manager.create_store(name, area, rent, utilities, total_counters, 
                total_halls, orders);
            return;
        }

        unsigned int total_floors = 0;
        input::input_number(total_floors, "Total floors> ");

        if (total_floors == 0)
        {
            cout << "Failed to add trade point: total floors should be > 0\n";
            return;
        }

        unsigned int section_count = 0;
        input::input_number(section_count, "Section count> ");

        if (section_count == 0)
        {
            cout << "Failed to add trade point: section count should be > 0\n";
            return;
        }

        vector<section_st> sections;
        section_st sec;
        for (unsigned int i = 0; i < section_count; ++i)
        {
            cout << "Section-" << to_string(i + 1) << " manager first name> ";
            getline(cin, sec.manager_first_name);

            cout << "Section-" << to_string(i + 1) << " manager middle name> ";
            getline(cin, sec.manager_middle_name);

            cout << "Section-" << to_string(i + 1) << " manager last name> ";
            getline(cin, sec.manager_last_name);

            input::input_number(sec.floor_number, "Floor number> ");

            sections.push_back(sec);
        }
        
        _manager.create_department_store(name, area, rent, utilities, total_counters, 
            total_halls, total_floors, sections, orders);
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
