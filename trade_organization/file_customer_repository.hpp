#pragma once
#include "file_repository_base.hpp"
#include "customer.hpp"

class file_customer_repository : public file_repository_base<customer>
{
public:
    file_customer_repository();
    ~file_customer_repository();

    string entity_to_string(customer* ent) override;
    customer* string_to_entity(string record) override;
    
};
