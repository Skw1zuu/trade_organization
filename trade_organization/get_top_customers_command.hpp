#pragma once
#include "command.hpp"
#include "customer_manager.hpp"

class get_top_customers_command : public command
{
public:
    get_top_customers_command(customer_manager& manager);

    void execute() override;

private:
    customer_manager& _manager;

};
