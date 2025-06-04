#include <exception>
#include <iostream>
#include "add_seller_command.hpp"
#include "input.hpp"
#include "util.hpp"

add_seller_command::add_seller_command(seller_manager& manager)
:
_manager(manager)
{}

void add_seller_command::execute()
{
    cout << "\n";
    
    string first_name;
    cout << "First name> ";
    getline(cin, first_name);

    string middle_name;
    cout << "Middle name> ";
    getline(cin, middle_name);

    string last_name;
    cout << "Last name> ";
    getline(cin, last_name);

    string phone_number;
    cout << "Phone number xxx-xxx-xx-xx> ";
    getline(cin, phone_number);
    
    if (!util::is_valid_phone_number(phone_number))
    {
        cout << "Failed to add seller: phone number is not valid\n";
        return;
    }

    float salary = 0;
    input::input_number(salary, "Salary> ");

    string trade_point_name;
    cout << "Trade point name> ";
    getline(cin, trade_point_name);

    try 
    {
        _manager.create_seller(first_name, middle_name, last_name, phone_number, salary, trade_point_name);
    } 
    catch (exception& ex) 
    {
        cout << ex.what() << endl;
    }
}
