#pragma once
#include "command.hpp"
#include "supplier_manager.hpp"

class get_suppliers_command : public command
{
public:
    get_suppliers_command(supplier_manager& manager);

    void execute() override;

private:
    supplier_manager& _manager;

};
