#include "supply.hpp"

supply::supply(const date cooperation_start, const date cooperation_end, 
        vector<unsigned int>& product_order_ids)
:
_number(_number_counter++),
_cooperation_start(cooperation_start),
_cooperation_end(cooperation_end),
_product_order_ids(product_order_ids)
{}
supply::supply(const unsigned int id, const unsigned int number, const date cooperation_start, 
        const date cooperation_end, vector<unsigned int>& product_order_ids)
:
entity(id),
_number(number),
_cooperation_start(cooperation_start),
_cooperation_end(cooperation_end),
_product_order_ids(product_order_ids)
{
    if (number >= _number_counter)
        _number_counter = number + 1;
}

unsigned int supply::get_number() const { return _number; }
date supply::get_cooperation_start() const { return _cooperation_start; }
date supply::get_cooperation_end() const { return _cooperation_end; }
const vector<unsigned int>& supply::get_product_order_ids() const { return _product_order_ids; }

unsigned int supply::_number_counter = 1;
