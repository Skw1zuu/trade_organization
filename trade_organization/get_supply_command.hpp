#pragma once
#include "command.hpp"
#include "supply_manager.hpp"

class get_supply_command : public command
{
public:
    get_supply_command(supply_manager& manager);

    void execute() override;

private:
    supply_manager& _manager;

};
