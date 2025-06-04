#pragma once
#include <string>
#include "trade_point.hpp"


class store : public trade_point
{
public:
    store(const string name, const float area, const float rent, const float utilities, 
        const unsigned int total_counters, vector<unsigned int>& product_order_ids, 
        const unsigned int total_halls);
    store(const unsigned int id, const string name, const float area, const float rent, 
        const float utilities, const unsigned int total_counters,  
        vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
        vector<unsigned int>& sale_ids, const unsigned int total_halls);

    unsigned int get_total_halls() const;

private:
    unsigned int _total_halls;
    
};
