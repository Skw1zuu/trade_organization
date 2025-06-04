#pragma once
#include "file_repository_base.hpp"
#include "product_order.hpp"

class file_product_order_repository : public file_repository_base<product_order>
{
public:
    file_product_order_repository();
    ~file_product_order_repository();

    string entity_to_string(product_order* ent) override;
    product_order* string_to_entity(string record) override;
    
};
