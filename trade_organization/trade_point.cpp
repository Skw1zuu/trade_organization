#include "trade_point.hpp"

trade_point::trade_point(const string name, const string type, const float area,
            const float rent, const float utilities, const unsigned int total_counters, 
            vector<unsigned int>& product_order_ids)
:
_name(name),
_type(type),
_area(area),
_rent(rent),
_utilities(utilities),
_total_counters(total_counters),
_product_order_ids(product_order_ids)
{}
trade_point::trade_point(const unsigned int id, const string name, const string type, 
    const float area, const float rent, const float utilities, const unsigned int total_counters, 
    vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
    vector<unsigned int>& sale_ids)
:
entity(id),
_name(name),
_type(type),
_area(area),
_rent(rent),
_utilities(utilities),
_total_counters(total_counters),
_seller_ids(seller_ids),
_product_order_ids(product_order_ids),
_sale_ids(sale_ids)
{}

string trade_point::get_name() const { return _name; }
string trade_point::get_type() const { return _type; }
float trade_point::get_area() const { return _area; }
float trade_point::get_utilities() const { return _utilities; }
float trade_point::get_rent() const { return _rent; }
unsigned int trade_point::get_total_counters() const { return _total_counters; }
const vector<unsigned int>& trade_point::get_seller_ids() const { return _seller_ids; }
const vector<unsigned int>& trade_point::get_product_order_ids() const { return _product_order_ids; }
const vector<unsigned int>& trade_point::get_sale_ids() const { return _sale_ids; }

void trade_point::add_seller_id(const unsigned int id)
{
    _seller_ids.push_back(id);
}
void trade_point::add_product_order_id(const unsigned int id)
{
    _product_order_ids.push_back(id);
}
void trade_point::add_sale_id(const unsigned int id)
{
    _sale_ids.push_back(id);
}
