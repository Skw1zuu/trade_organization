#include "kiosk.hpp"

kiosk::kiosk(const string name, const float area, const float rent, const float utilities, 
        const unsigned int total_counters, vector<unsigned int>& product_order_ids)
:
trade_point(name, "KIOSK", area, rent, utilities, total_counters, product_order_ids)
{}

kiosk::kiosk(const unsigned int id, const string name, const float area, 
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
        vector<unsigned int>& sale_ids)
:
trade_point(id, name, "KIOSK", area, rent, utilities, total_counters, seller_ids, 
    product_order_ids, sale_ids)
{}     
