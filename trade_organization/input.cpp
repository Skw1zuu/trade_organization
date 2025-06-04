#include <iostream>
#include <limits>
#include "input.hpp"

void input::input_number(unsigned int& out, const string question)
{
    while (true) 
    {
        cout << question;
        cin >> out;

        if (std::cin.fail()) 
        {
            cout << "Failed to parse natural number: entered number is not valid\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
            break;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void input::input_number(float& out, const string question)
{
    while (true) 
    {
        cout << question;
        cin >> out;

        if (std::cin.fail()) 
        {
            cout << "Failed to parse floating point number: entered number is not valid\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
            break;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
