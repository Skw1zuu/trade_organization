#pragma once
#include <vector>
#include "entity.hpp"
#include "date.hpp"

using namespace std;

class sale : public entity
{
public:
    sale(const date sale_date, vector<unsigned int>& product_order_ids, const unsigned int seller_id,
        const unsigned int customer_id, const unsigned int trade_point_id);
    sale(const unsigned int id, const date sale_date, vector<unsigned int>& product_order_ids, 
        const unsigned int seller_id, const unsigned int customer_id, 
        const unsigned int trade_point_id);
    
    date get_sale_date() const;
    vector<unsigned int> get_product_order_ids() const;
    unsigned int get_seller_id() const;
    unsigned int get_customer_id() const;
    unsigned int get_trade_point_id() const;

private:
    date _sale_date;
    vector<unsigned int> _product_order_ids;
    unsigned int _seller_id;
    unsigned int _custormer_id;
    unsigned int _trade_point_id;

};
