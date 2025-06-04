#include <iostream>
#include <string>
#include "help_command.hpp"

help_command::help_command(const vector<string>& commands)
:
_commands(commands)
{}

void help_command::execute()
{
    cout << "\n";

    cout << "-------------------------\n";
    for (unsigned int i = 0; i < _commands.size(); ++i)
    {
        cout << to_string(i + 1) << ": " << _commands[i] << endl;
    }
    cout << "-------------------------\n";
}
