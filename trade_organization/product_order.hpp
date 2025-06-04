#pragma once
#include <string>
#include "entity.hpp"

using namespace std;

struct product_order_st
{
    string product_name;
    string product_type;
    unsigned int quantity;
    float price_per_unit;
};
struct product_order_quantity_st
{
    string product_name;
    string product_type;
    unsigned int quantity;
};

class product_order : public entity
{
public:
    product_order(const unsigned int product_id, const unsigned int quantity, 
        const float price_per_unit);
    product_order(const unsigned int id, const unsigned int product_id, 
        const unsigned int quantity, const float price_per_unit);
    
    unsigned int get_product_id() const;
    unsigned int get_quantity() const;
    float get_price_per_unit() const;
    
    void set_quantity(const unsigned int quantity);

private:
    unsigned int _product_id;
    unsigned int _quantity;
    float _price_per_unit;

};
