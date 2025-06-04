#pragma once
#include <string>
#include <vector>
#include "entity.hpp"

using namespace std;

class trade_point : public entity
{
public:
    string get_name() const;
    string get_type() const;
    float get_area() const;
    float get_rent() const;
    float get_utilities() const;
    unsigned int get_total_counters() const;
    const vector<unsigned int>& get_seller_ids() const;
    const vector<unsigned int>& get_product_order_ids() const;
    const vector<unsigned int>& get_sale_ids() const;

    void add_seller_id(const unsigned int id);
    void add_product_order_id(const unsigned int id);
    void add_sale_id(const unsigned int id);

protected:
    trade_point(const string name, const string type, const float area,
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& product_order_ids);
    trade_point(const unsigned int id, const string name, const string type, const float area,
        const float rent, const float utilities, const unsigned int total_counters, 
        vector<unsigned int>& seller_ids, vector<unsigned int>& product_order_ids, 
        vector<unsigned int>& sale_ids);

private:
    string _name;
    string _type;
    float _area;
    float _rent;
    float _utilities;
    unsigned int _total_counters;
    vector<unsigned int> _seller_ids;
    vector<unsigned int> _product_order_ids;
    vector<unsigned int> _sale_ids;

};
