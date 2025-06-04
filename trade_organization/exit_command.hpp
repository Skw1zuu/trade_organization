#pragma once
#include "command.hpp"

class exit_command : public command
{
public:
    void execute() override;

};
