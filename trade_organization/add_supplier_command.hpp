#pragma once
#include "command.hpp"
#include "supplier_manager.hpp"

class add_supplier_command : public command
{
public:
    add_supplier_command(supplier_manager& manager);

    void execute() override;

private:
    supplier_manager& _manager;

};
