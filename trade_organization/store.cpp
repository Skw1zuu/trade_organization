#include "store.hpp"

store::store(const string name, const float area, const float rent, const float utilities, 
    const unsigned int total_counters, vector<unsigned int>& product_order_ids, 
    const unsigned int total_halls)
:
trade_point(name, "STORE", area, rent, utilities, total_counters, product_order_ids),
_total_halls(total_halls)
{}
store::store(const unsigned int id, const string name, const float area, const float rent, 
    const float utilities, const unsigned int total_counters,  
    vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
    vector<unsigned int>& sale_ids, const unsigned int total_halls)
:
trade_point(id, name, "STORE", area, rent, utilities, total_counters, seller_ids, 
    product_order_ids, sale_ids),
_total_halls(total_halls)
{}

unsigned int store::get_total_halls() const { return _total_halls; }
