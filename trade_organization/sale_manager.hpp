#pragma once
#include <string>
#include <vector>
#include "date.hpp"
#include "product_order.hpp"
#include "product.hpp"
#include "repository.hpp"

using namespace std;

class sale_manager
{
public:
    sale_manager(sale_repository& sale_repo, trade_point_repository& trade_point_repo, 
        product_order_repository& product_order_repo, product_repository& product_repo, 
        seller_repository& seller_repo, customer_repository& customer_repo);

    void create_sale(const date sale_date, vector<product_order_quantity_st>& product_orders, 
        const string customer_name, const string customer_phone_number, 
        const string seller_phone_number, const string trade_point_name);

    unsigned int get_sale_amount_by_product(const product_st prod, 
        const date start, const date end) const;
    unsigned int get_sale_amount_by_product_and_tp_type(const product_st prod, 
        const string trade_point_type, const date start, const date end) const;
    unsigned int get_sale_amount_by_product_and_tp_name(const product_st prod, 
        const string trade_point_name, const date start, const date end) const;
    float get_tp_turnover(const string trade_point_name, const date start, const date end) const;
    float get_tp_turnover(const vector<string>& trade_point_names, const date start, 
            const date end) const;

private:
    sale_repository& _sale_repo;
    trade_point_repository& _trade_point_repo;
    product_order_repository& _product_order_repo;
    product_repository& _product_repo;
    seller_repository& _seller_repo;
    customer_repository& _customer_repo;

    unsigned int get_sale_amount_by_prod(const vector<unsigned int>& sale_ids, 
        const product_st& prod, const date start, const date end) const;
    trade_point* get_tp_by_name(const string trade_point_name) const;
    
};
