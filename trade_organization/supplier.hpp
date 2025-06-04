#pragma once
#include <string>
#include <vector>
#include "entity.hpp"

using namespace std;

class supplier : public entity
{
public:
    supplier(const string name, vector<unsigned int>& product_order_ids);
    supplier(const unsigned int id, const string name, vector<unsigned int>& product_order_ids, 
        vector<unsigned int>& supply_ids);

    string get_name() const;
    const vector<unsigned int>& get_product_order_ids() const;
    const vector<unsigned int>& get_supply_ids() const;
    
    void add_supply_id(const unsigned int id);

private:
    string _name;
    vector<unsigned int> _product_order_ids; // quintity per day
    vector<unsigned int> _supply_ids;

};
