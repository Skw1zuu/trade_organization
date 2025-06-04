#include "sale.hpp"

sale::sale(const date sale_date, vector<unsigned int>& product_order_ids, const unsigned int seller_id,
     const unsigned int customer_id, const unsigned int trade_point_id)
:
_sale_date(sale_date),
_product_order_ids(product_order_ids),
_seller_id(seller_id),
_custormer_id(customer_id),
_trade_point_id(trade_point_id)
{}
sale::sale(const unsigned int id, const date sale_date, vector<unsigned int>& product_order_ids, 
     const unsigned int seller_id, const unsigned int customer_id, 
     const unsigned int trade_point_id)
:
entity(id),
_sale_date(sale_date),
_product_order_ids(product_order_ids),
_seller_id(seller_id),
_custormer_id(customer_id),
_trade_point_id(trade_point_id)
{}

date sale::get_sale_date() const { return _sale_date; }
vector<unsigned int> sale::get_product_order_ids() const { return _product_order_ids; }
unsigned int sale::get_seller_id() const { return _seller_id; }
unsigned int sale::get_customer_id() const { return  _custormer_id; }
unsigned int sale::get_trade_point_id() const { return _trade_point_id; }
