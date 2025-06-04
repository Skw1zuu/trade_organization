#pragma once
#include "file_repository_base.hpp"
#include "sale.hpp"

class file_sale_repository : public file_repository_base<sale>
{
public:
    file_sale_repository();
    ~file_sale_repository();

    string entity_to_string(sale* ent) override;
    sale* string_to_entity(string record) override;
    
};
