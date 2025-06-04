#pragma once
#include <string>
#include <vector>
#include "repository.hpp"
#include "date.hpp"
#include "seller.hpp"
#include "trade_point.hpp"

using namespace std;

class seller_manager 
{
public:
    seller_manager(seller_repository& seller_repo, trade_point_repository& trade_point_repo, 
        sale_repository& sale_repo, product_order_repository& product_order_repo);

    void create_seller(const string first_name, const string middle_name, const string last_name,
        const string phone_number, const float salary, const string trade_point_name);

    float get_seller_performance(const string phone_number, const date start, const date end) const;
    float get_seller_performance_by_tp_type(const string phone_number, 
        const string trade_point_type, const date start, const date end) const;
    float get_seller_performance_by_tp_name(const string phone_number, 
        const string trade_point_name, const date start, const date end) const;
    const vector<seller*>& get_sellers() const;
    vector<seller*> get_sellers_by_tp_type(const string trade_point_type) const;
    vector<seller*> get_sellers_by_tp_name(const string trade_point_name) const;
    seller* get_seller_by_phone_number(const string phone_number) const;

private:
    seller_repository& _seller_repo;
    trade_point_repository& _trade_point_repo;
    sale_repository& _sale_repo;
    product_order_repository& _product_order_repo;

    seller* get_seller_by_phone_number(const string phone_number, 
        const vector<seller*>& sellers) const;
    trade_point* get_tp_by_name(const string trade_point_name) const;
    float get_seller_performance_by_sales(const vector<unsigned int>& sale_ids, 
        seller* sel, const date start, const date end) const;
    vector<trade_point*> get_tps_by_type(const string trade_point_type) const;
    
};
