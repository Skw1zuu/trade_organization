#pragma once
#include "command.hpp"
#include "sale_manager.hpp"

class add_sale_command : public command
{
public:
    add_sale_command(sale_manager& manager);

    void execute() override;

private:
    sale_manager& _manager;

};
