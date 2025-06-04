#pragma once
#include "file_repository_base.hpp"
#include "supply.hpp"

class file_supply_repository : public file_repository_base<supply>
{
public:
    file_supply_repository();
    ~file_supply_repository();

    string entity_to_string(supply* ent) override;
    supply* string_to_entity(string record) override;
    
};
