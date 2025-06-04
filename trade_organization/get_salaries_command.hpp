#pragma once
#include "command.hpp"
#include "seller_manager.hpp"

class get_salaries_command : public command
{
public:
    get_salaries_command(seller_manager& manager);

    void execute() override;

private:
    seller_manager& _manager;

};
