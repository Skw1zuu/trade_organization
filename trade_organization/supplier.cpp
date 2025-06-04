#include "supplier.hpp"

supplier::supplier(const string name, vector<unsigned int>& product_order_ids)
:
_name(name),
_product_order_ids(product_order_ids)
{}
supplier::supplier(const unsigned int id, const string name, 
    vector<unsigned int>& product_order_ids, vector<unsigned int>& supply_ids)
:
entity(id),
_name(name),
_product_order_ids(product_order_ids),
_supply_ids(supply_ids)
{}

string supplier::get_name() const { return _name; }
const vector<unsigned int>& supplier::get_product_order_ids() const 
{ 
    return _product_order_ids; 
}
const vector<unsigned int>& supplier::get_supply_ids() const { return _supply_ids; }

void supplier::add_supply_id(const unsigned int id)
{
    _supply_ids.push_back(id);
}
