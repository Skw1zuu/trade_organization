#pragma once
#include "file_repository_base.hpp"
#include "seller.hpp"

class file_seller_repository : public file_repository_base<seller>
{
public:
    file_seller_repository();
    ~file_seller_repository();

    string entity_to_string(seller* ent) override;
    seller* string_to_entity(string record) override;
    
};
