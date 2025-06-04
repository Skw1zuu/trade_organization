#pragma once
#include "command.hpp"
#include "customer_manager.hpp"

class get_customers_by_product_command : public command
{
public:
    get_customers_by_product_command(customer_manager& manager);

    void execute() override;

private:
    customer_manager& _manager;

};
