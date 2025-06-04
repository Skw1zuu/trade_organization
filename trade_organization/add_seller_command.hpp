#pragma once
#include "command.hpp"
#include "seller_manager.hpp"

class add_seller_command : public command
{
public:
    add_seller_command(seller_manager& manager);

    void execute() override;

private:
    seller_manager& _manager;

};
