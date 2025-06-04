#pragma once
#include "file_repository_base.hpp"
#include "product.hpp"

class file_product_repository : public file_repository_base<product>
{
public:
    file_product_repository();
    ~file_product_repository();

    string entity_to_string(product* ent) override;
    product* string_to_entity(string record) override;
    
};
