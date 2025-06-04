#pragma once
#include "command.hpp"
#include "trade_point_manager.hpp"

class add_trade_point_command : public command
{
public:
    add_trade_point_command(trade_point_manager& manager);

    void execute() override;

private:
    trade_point_manager& _manager;

};
