
#pragma once
#include "command.hpp"
#include "trade_point_manager.hpp"

class get_sales_efficiency_command : public command
{
public:
    get_sales_efficiency_command(trade_point_manager& manager);

    void execute() override;

private:
    trade_point_manager& _manager;

};
