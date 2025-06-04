#pragma once
#include <string>
#include <vector>
#include "command.hpp"

using namespace std;

class help_command : public command
{
public:
    help_command(const vector<string>& commands);

    void execute() override;

private:
    vector<string> _commands;

};
