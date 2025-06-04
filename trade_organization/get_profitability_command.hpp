#pragma once
#include "command.hpp"
#include "trade_point_manager.hpp"

class get_profitability_command : public command
{
public:
    get_profitability_command(trade_point_manager& manager);

    void execute() override;

private:
    trade_point_manager& _manager;

};
