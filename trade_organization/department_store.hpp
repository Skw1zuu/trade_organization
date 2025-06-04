#pragma once
#include <vector>
#include "trade_point.hpp"

using namespace std;

class departament_store : public trade_point
{
public:
    departament_store(const string name, const float area,
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& product_order_ids, vector<unsigned int>& section_ids, 
        const unsigned int total_floors, const unsigned int total_halls);
    departament_store(const unsigned int id, const string name, const float area,
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
        vector<unsigned int>& sale_ids, vector<unsigned int>& section_ids, 
        const unsigned int total_floors, const unsigned int total_halls);
    
    vector<unsigned int> get_section_ids() const;
    unsigned int get_total_floors() const;
    unsigned int get_total_halls() const;

private:
    vector<unsigned int> _section_ids;
    unsigned int _total_floors;
    unsigned int _total_halls;
    
};
