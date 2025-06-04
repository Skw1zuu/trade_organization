#pragma once
#include "file_repository_base.hpp"
#include "supplier.hpp"

class file_supplier_repository : public file_repository_base<supplier>
{
public:
    file_supplier_repository();
    ~file_supplier_repository();

    string entity_to_string(supplier* ent) override;
    supplier* string_to_entity(string record) override;
    
};
