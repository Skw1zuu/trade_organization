#pragma once
#include "command.hpp"
#include "sale_manager.hpp"

class get_turnover_command : public command
{
public:
    get_turnover_command(sale_manager& manager);

    void execute() override;

private:
    sale_manager& _manager;

};
