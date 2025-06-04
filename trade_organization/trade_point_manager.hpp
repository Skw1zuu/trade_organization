#pragma once
#include <vector>
#include <string>
#include <utility>
#include "repository.hpp"
#include "product_order.hpp"
#include "product.hpp"
#include "date.hpp"
#include "trade_point.hpp"
#include "section.hpp"

using namespace std;

class trade_point_manager
{
public:
    trade_point_manager(trade_point_repository& trade_point_repo, product_repository& product_repo,
        product_order_repository& product_order_repo, section_repository& section_repo,
        sale_repository& sale_repo, seller_repository& seller_repo);

    void create_kiosk(const string name, const float area, const float rent, const float utilities, 
        const unsigned int total_counters, vector<product_order_st>& product_orders);
    void create_store(const string name, const float area, const float rent, const float utilities, 
        const unsigned int total_counters, const unsigned int total_halls, 
        vector<product_order_st>& product_orders);
    void create_department_store(const string name, const float area, const float rent, 
        const float utilities, const unsigned int total_counters, const unsigned int total_halls, 
        const unsigned int total_floors, vector<section_st>& sections, 
        vector<product_order_st>& product_orders);

    vector<product_order_st> get_stock_by_tp_name(const string name) const;
    vector<pair<trade_point*, product_order_st>> get_orders_by_product(const product_st prod) const;
    vector<pair<trade_point*, product_order_st>> get_orders_by_product_and_tp_type(const product_st prod, 
        const string trade_point_type) const;
    pair<trade_point*, product_order_st> get_order_by_product_and_tp_name(const product_st prod, 
        const string trade_point_name) const;
    vector<pair<trade_point*, float>> get_area_amount_relation(const string trade_point_type) const;
    vector<pair<trade_point*, float>> get_hall_amount_relation(const string trade_point_type) const;
    vector<pair<trade_point*, float>> get_counters_amount_relation(
        const string trade_point_type) const;
    float get_tp_profitability(const string trade_point_name, const date start, 
        const date end) const;
    trade_point* get_trade_point_by_name(const string trade_point_name) const;

private:
    trade_point_repository& _trade_point_repo;
    product_repository& _product_repo;
    product_order_repository& _product_order_repo;
    section_repository& _section_repo;
    sale_repository& _sale_repo;
    seller_repository& _seller_repo;

    vector<unsigned int> create_and_validate_tp_product_orders(const string name, 
        vector<product_order_st>& product_orders) const;
    trade_point* get_tp_by_name(const string trade_point_name) const;
    product_order_st get_product_order_by_tp(trade_point* tp, 
        const product_st& prod) const;
    float get_tp_sale_amount(trade_point* tp) const;
    float get_tp_sale_amount(trade_point* tp, const date start, const date end) const;

};
