#pragma once
#include "command.hpp"
#include "trade_point_manager.hpp"

class get_prices_command : public command
{
public:
    get_prices_command(trade_point_manager& manager);

    void execute() override;

private:
    trade_point_manager& _manager;

};
