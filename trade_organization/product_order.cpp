#include "product_order.hpp"

product_order::product_order(const unsigned int product_id, const unsigned int quantity,
    const float price_per_unit)
:
_product_id(product_id),
_quantity(quantity),
_price_per_unit(price_per_unit)
{}
product_order::product_order(const unsigned int id, const unsigned int product_id, 
    const unsigned int quantity, const float price_per_unit)
:
entity(id),
_product_id(product_id),
_quantity(quantity),
_price_per_unit(price_per_unit)
{}

unsigned int product_order::get_product_id() const { return _product_id; }
unsigned int product_order::get_quantity() const { return  _quantity; }
float product_order::get_price_per_unit() const { return _price_per_unit; }
void product_order::set_quantity(const unsigned int quantity)
{
    _quantity = quantity;
}
