#pragma once
#include "command.hpp"
#include "supply_manager.hpp"

class add_supply_command : public command
{
public:
    add_supply_command(supply_manager& manager);

    void execute() override;

private:
    supply_manager& _manager;

};
