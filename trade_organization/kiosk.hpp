#pragma once
#include "trade_point.hpp"

class kiosk : public trade_point
{
public:
    kiosk(const string name, const float area, const float rent, const float utilities, 
        const unsigned int total_counters, vector<unsigned int>& product_order_ids);
    kiosk(const unsigned int id, const string name, const float area,
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
        vector<unsigned int>& sale_ids);
};
