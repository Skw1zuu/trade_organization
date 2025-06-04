#pragma once
#include <vector>
#include "entity.hpp"
#include "date.hpp"
#include "product_order.hpp"

using namespace std;

struct supply_st
{
    unsigned int supply_number;
    date cooperation_start;
    date cooperation_end;
    vector<product_order_st> orders;
};

class supply : public entity
{
public:
    supply(const date cooperation_start, const date cooperation_end, 
        vector<unsigned int>& product_order_ids);
    supply(const unsigned int id, const unsigned int number, const date cooperation_start, 
        const date cooperation_end, vector<unsigned int>& product_order_ids);
    
    unsigned int get_number() const;
    date get_cooperation_start() const;
    date get_cooperation_end() const;
    const vector<unsigned int>& get_product_order_ids() const;

private:
    static unsigned int _number_counter;
    unsigned int _number;
    date _cooperation_start;
    date _cooperation_end;
    vector<unsigned int> _product_order_ids;
    
};