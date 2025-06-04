#pragma once
#include <string>
#include <vector>
#include "repository.hpp"
#include "customer.hpp"

using namespace std;

class customer_manager
{
public:
    customer_manager(customer_repository& customer_repo, sale_repository& sale_repo, 
        trade_point_repository& trade_point_repo, product_repository& product_repo, 
        product_order_repository& product_order_repo);

    vector<customer*> get_customers_by_purchase(const string product_type, 
        const date start, const date end) const;
    vector<customer*> get_customers_by_purchase(const product_st prod, 
        const unsigned int min_quantity) const;
    vector<customer*> get_customers_by_product(product_st prod, const date start, 
        const date end) const;
    vector<customer*> get_customers_by_product_and_tp_type(const product_st prod, 
        const string trade_point_type, const date start, const date end) const;
    vector<customer*> get_customers_by_product_and_tp_name(const product_st prod, 
        const string trade_point_name, const date start, const date end) const;
    vector<pair<customer*, float>> get_top_active_customers() const;
    vector<pair<customer*, float>> get_top_active_customers_by_tp_type(
        const string trade_point_type) const;
    vector<pair<customer*, float>> get_top_active_customers_by_tp_name(
        const string trade_point_name) const;

private:
    customer_repository& _customer_repo;
    sale_repository& _sale_repo;
    trade_point_repository& _trade_point_repo;
    product_repository& _product_repo;
    product_order_repository& _product_order_repo;

};
